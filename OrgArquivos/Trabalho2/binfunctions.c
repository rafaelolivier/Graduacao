/*
Funções para manipulação de arquivos binários, como read e write

Rafael Olivier Cardoso
9436166
*/

#include "binfunctions.h"


/*
Inicializa um bloco de dados
Não há parâmetros
Retorna bloco de dados inicializado e com telefoneServidor alocado
*/
DATA createBlock(){
    DATA block;

    block.removido = '-';   //'-' indica não removido, '*' indica removido
    block.encadeamentoLista = -1;   //Byte offset da próxima remoção, -1 em caso de dados não removidos
    block.tamRegistro = 0;  //Tamanho do bloco de dados
    block.idServidor = 0;   //grava o id do servidor
    block.salarioServidor = 0;  //grava o salário do servidor
    block.telefoneServidor = NULL;  //grava o telefone do servidor - tem sempre 14 bytes
    block.tamString1 = 0; //grava o tamanho do nome
    block.delimCampo4 = 'n'; //grava o delimitador 'n' do nome
    block.nomeServidor = NULL;  //grava o nome do servidor
    block.tamString2 = 0; //grava o tamanho do cargo
    block.delimCampo5 = 'c';  //Grava os delimitador 'c' do cargo
    block.cargoServidor = NULL; //grava o cargo.
    block.telefoneServidor = (char*) calloc (14, sizeof(char)); //Não terá \0, exige cuidado na manipulação

    return block;
}


/*
Escreve um bloco de dados em arquivo Binário
Parâmetros: Bloco de dados a ser escrito, File binário, booleans dv1 e dv2 que indicam se há campos variáveis 1 e 2 a serem escritos
Retorno: Retorna o bytecounter atualizado (MAX 32000, então zero) e há uma atualização no arquivo binário.
*/
int binWriteBlock(DATA block, FILE* bin, int dv1, int dv2, long int byteCounter, int tamAnterior){

    char fill = '@';
    int a = 0;

    //Verificação se o registro caberá na página de disco, antes de gravar
    if(block.tamRegistro + byteCounter <= 32000){
        byteCounter += block.tamRegistro;
    }else{
        fseek(bin, -(tamAnterior+4), SEEK_CUR);
        int newSize;
        newSize = tamAnterior+32000-byteCounter;
        fwrite(&newSize, sizeof(int), 1, bin);
        fseek(bin, tamAnterior, SEEK_CUR);
        //Essa página de disco não terá espaço suficiente, preencha com '@'
        for(a = 32000-byteCounter; a > 0; a--){
            fwrite(&fill, sizeof(char), 1, bin);
        }
        byteCounter = 0;
    }
    if(block.removido == '*'){
        fwrite(&block.removido, sizeof(char), 1, bin);
        fwrite(&block.tamRegistro, sizeof(int), 1, bin);
        fwrite(&block.encadeamentoLista, sizeof(long int), 1, bin);
        for(a = 13; a <= block.tamRegistro; a++) fwrite(&fill, sizeof(char), 1, bin);
    }else{
        //Bloco de chamadas de fwrite, onde os registros serão de fato escritos no binário
        //Os campos de tamanho variável só escrevem se não forem nulos
        fwrite(&block.removido, sizeof(char), 1, bin);
        fwrite(&block.tamRegistro, sizeof(int), 1, bin);
        fwrite(&block.encadeamentoLista, sizeof(long int), 1, bin);
        fwrite(&block.idServidor, sizeof(int), 1, bin);
        fwrite(&block.salarioServidor, sizeof(double), 1, bin);
        fwrite(block.telefoneServidor, sizeof(char), 14, bin);
        if(dv1 != 1){
            fwrite(&block.tamString1, sizeof(int), 1, bin);
            fwrite(&block.delimCampo4, sizeof(char), 1, bin);
            fwrite(block.nomeServidor, sizeof(char), block.tamString1-1, bin);
        }
        if(dv2 != 1){
            fwrite(&block.tamString2, sizeof(int), 1, bin);
            fwrite(&block.delimCampo5, sizeof(char), 1, bin);
            fwrite(block.cargoServidor, sizeof(char), block.tamString2-1, bin);
        }
    }

    return byteCounter;
}


/*
Lê um bloco de dados em arquivo Binário, engole @ para preencher páginas de disco e atualiza o contador de bytes.
Parâmetros: Arquivo Binários, Bloco de dados, Endereço do contador de bytes (para atualizar na função)
Retorno: Bloco de dados lidos.
*/
DATA binReadBlock(FILE* bin, DATA block, long int* byteCounter){

    char fill = '@';
    int fillCounter = 0;
    char aux = 1;
    int i = 0;

    fread(&block.removido, sizeof(char), 1, bin);
    if(block.removido == '*' && !feof(bin)){
        fread(&block.tamRegistro, sizeof(int), 1, bin);
        fread(&block.encadeamentoLista, sizeof(long int), 1, bin);
        fill = '@';
        for(i = 8; i < block.tamRegistro; i++){
            fread(&fill, sizeof(char), 1, bin);
        }
        (*byteCounter) += block.tamRegistro;
        return block;
    }

    if(!feof(bin)){
        fread(&block.tamRegistro, sizeof(int), 1, bin);
        fseek(bin, block.tamRegistro-1, SEEK_CUR);
        fread(&aux, sizeof(char), 1, bin);
        while(aux == '@' && block.tamRegistro > 39){
            fillCounter++;
            fseek(bin, -2, SEEK_CUR);
            fread(&aux, sizeof(char), 1, bin);
        }
        fseek(bin, -(block.tamRegistro-fillCounter), SEEK_CUR);
        (*byteCounter) += block.tamRegistro;

        //Leituras dos outros campos fixos
        fread(&block.encadeamentoLista, sizeof(long int), 1, bin);
        fread(&block.idServidor, sizeof(int), 1, bin);
        fread(&block.salarioServidor, sizeof(double), 1, bin);
        fread(block.telefoneServidor, sizeof(char), 14, bin);

        if(block.tamRegistro-34-fillCounter > 0){
            fread(&block.tamString1, sizeof(int), 1, bin);
            fread(&block.delimCampo4, sizeof(char), 1, bin);
            block.nomeServidor = (char*) realloc (block.nomeServidor, block.tamString1*sizeof(char*));
            fread(block.nomeServidor, sizeof(char), block.tamString1-1, bin);

            if(block.tamRegistro-34-fillCounter-4-block.tamString1 > 0){
                fread(&block.tamString2, sizeof(int), 1, bin);
                fread(&block.delimCampo5, sizeof(char), 1, bin);
                block.cargoServidor = (char*) realloc (block.cargoServidor, block.tamString2*sizeof(char*));
                fread(block.cargoServidor, sizeof(char), block.tamString2-1, bin);
            } else block.delimCampo5 = 'v';
        }else block.delimCampo4 = 'v';

        if(fillCounter > 0) for(; fillCounter > 0; fillCounter--) fread(&aux, sizeof(char), 1, bin);
    }

    return block;
}

void escreverCabecalho(FILE* bin, REGISTRO cabecalho){

    fwrite(cabecalho.status, sizeof(char), 1, bin);
    fwrite(&cabecalho.topoLista, sizeof(long int), 1, bin);
    fwrite(cabecalho.tagCampo1, sizeof(char), 1, bin);
    fwrite(cabecalho.desCampo1, sizeof(char), 40, bin);
    fwrite(cabecalho.tagCampo2, sizeof(char), 1, bin);
    fwrite(cabecalho.desCampo2, sizeof(char), 40, bin);
    fwrite(cabecalho.tagCampo3, sizeof(char), 1, bin);
    fwrite(cabecalho.desCampo3, sizeof(char), 40, bin);
    fwrite(cabecalho.tagCampo4, sizeof(char), 1, bin);
    fwrite(cabecalho.desCampo4, sizeof(char), 40, bin);
    fwrite(cabecalho.tagCampo5, sizeof(char), 1, bin);
    fwrite(cabecalho.desCampo5, sizeof(char), 40, bin);
    fwrite(cabecalho.preenchePaginaDisco, sizeof(char), 31786, bin);
}

REGISTRO lerCabecalho(FILE* bin, REGISTRO cabecalho){

    fread(cabecalho.status, sizeof(char), 1, bin);
    fread(&cabecalho.topoLista, sizeof(long int), 1, bin);
    fread(cabecalho.tagCampo1, sizeof(char), 1, bin);
    fread(cabecalho.desCampo1, sizeof(char), 40, bin);
    fread(cabecalho.tagCampo2, sizeof(char), 1, bin);
    fread(cabecalho.desCampo2, sizeof(char), 40, bin);
    fread(cabecalho.tagCampo3, sizeof(char), 1, bin);
    fread(cabecalho.desCampo3, sizeof(char), 40, bin);
    fread(cabecalho.tagCampo4, sizeof(char), 1, bin);
    fread(cabecalho.desCampo4, sizeof(char), 40, bin);
    fread(cabecalho.tagCampo5, sizeof(char), 1, bin);
    fread(cabecalho.desCampo5, sizeof(char), 40, bin);
    fread(cabecalho.preenchePaginaDisco, sizeof(char), 31786, bin);

    return cabecalho;
}