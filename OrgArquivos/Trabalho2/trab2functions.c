#include "trab2functions.h"

/*
Remove registros em um arquivo binário
O registro deve ser selecionado por uma de suas 5 casas (id, salario, telefone, nome ou cargo)
Remove todos os registros que atendem ao critério inserido
Parâmetros: Nome do arquivo binário
Não há retorno, mas há uma mudança no arquivo binário.
*/
void removerRegistro(char* fileName){

    FILE* bin = fopen(fileName, "r+b");
    
    //A primeira posição de byteOffSetList terá o número de resultados encontrados
    //As posições seguintes indica as posições dos resultados no arquivo
    //A última posição é preenchida com -1 para evitar segfault uma vez que todas as pesquisas tenham sido feitas
    long int* byteOffSetList = NULL;

    int searchIndex = 0;
        
    searchIndex = definirCampo();
    byteOffSetList = pesquisar(fileName, searchIndex, 1);
        
    int i = 0, j = 0, removed = 1;
    //for(i = 0; i < byteOffSetList[0]; i++) printf("%ld\n", byteOffSetList[i+1]);
    i = 0;

    if(byteOffSetList[0] > 0){

        //Contadores e booleans
        int delete = 0; //boolean que indica se um registro deve ser apagado
        long int byteCounter, listByteCounter = -1, listByteCounterAnt = -1;    //Grava a quantia de bytes lida
        char fill = '@';  //Tratamento das páginas de disco preenchidas com @

        fseek(bin, 1, SEEK_SET);
        fread(&listByteCounter, sizeof(long int), 1, bin);

        DATA block = createBlock();
        DATA auxBlock;

        for(i = 1; i < byteOffSetList[0]-1; i++){
            
            fseek(bin, byteOffSetList[i], SEEK_SET);
            byteCounter = byteOffSetList[i];
            block = binReadBlock(bin, block, &byteCounter);
            block.removido = '*';

            removed = 1;
            while(removed == 1){
                fseek(bin, listByteCounter, SEEK_SET);
                auxBlock = binReadBlock(bin, auxBlock, &byteCounter);
                if(block.tamRegistro < auxBlock.tamRegistro){
                    block.encadeamentoLista = listByteCounter;
                    fseek(bin, byteOffSetList[i], SEEK_SET);
                    fwrite(&block.removido, sizeof(char), 1, bin);
                    fwrite(&block.tamRegistro, sizeof(int), 1, bin);
                    fwrite(&block.encadeamentoLista, sizeof(long int), 1, bin);
                    for(j = 8; j < block.tamRegistro; j++) fwrite(&fill, sizeof(char), 1, bin);

                    if(listByteCounterAnt == -1){
                        fseek(bin, 1, SEEK_SET);
                        fwrite(&byteOffSetList[i], sizeof(long int), 1, bin);
                    }else{
                        fseek(bin, listByteCounterAnt, SEEK_CUR);
                        fwrite(&byteOffSetList[i], sizeof(long int), 1, bin);
                    }
                    removed = 0;
                }
                else{
                    if(auxBlock.encadeamentoLista == -1){
                        fseek(bin, -auxBlock.tamRegistro, SEEK_CUR);
                        fwrite(&byteOffSetList[i], sizeof(long int), 1, bin);
                        removed = 0;
                    }
                    listByteCounterAnt = listByteCounter;
                    listByteCounter = auxBlock.encadeamentoLista;
                }
            }
        }


        free(block.telefoneServidor);
        free(block.nomeServidor);
        free(block.cargoServidor);
        free(auxBlock.telefoneServidor);
        free(auxBlock.nomeServidor);
        free(auxBlock.cargoServidor);
    }
    free(byteOffSetList);
    fclose(bin);
}

/*
Insere registros em um arquivo binário
O modo de inserção utilizado foi o Best-Fit e o espaço que sobra em cada campo  não é reaproveitado e fica preenchido com '@'
Parâmetros: Nome do arquivo
Não há retorno, mas há uma mudança no arquivo binário.
*/
void inserirRegistro(char* fileName){

    FILE* bin = fopen(fileName, "r+b");

    int a = 0, b = 0;
    int tamAnterior;
    int dv1 = 0, dv2 = 0;
    char aux = 0;

    char* str1 = NULL;
    char* str2 = NULL;
    char* str3 = NULL;
    DATA insertionBlock = createBlock();

    //Pega o id
    str1 = getName();
    insertionBlock.idServidor = atoi(str1);
    
    //Pega o salário
    str2 = getName();
    if(str2[0] == 'N' && str2[1] == 'U' && str2[2] == 'L' && str2[3] == 'O') insertionBlock.salarioServidor = -1;
    else insertionBlock.salarioServidor = atof(str2);

    //Pega o telefone
    str3 = getName();
    if(str3[0] == 'N' && str3[1] == 'U' && str3[2] == 'L' && str3[3] == 'O'){
        insertionBlock.telefoneServidor[0] = '\0';
        for(a = 1; a < 14; a++) insertionBlock.telefoneServidor[a] = '@';
    }else for(a=1; a < 15; a++) insertionBlock.telefoneServidor[a-1] = str3[a];
    insertionBlock.tamRegistro = 39;

    //Pega o nome e tamString1
    aux = getchar(); //Pega primeiro caractere, é obrigatoriamente " ou N
    if(aux == 'N'){
        for(a = 0; a < 3; a++)getchar(); //Pega 'ULO'
        dv1 = 1;
    }else{
        a = 0;
        aux = getchar();
        while(aux != '"' && aux != EOF && aux != '\n'){
            insertionBlock.nomeServidor = (char*) realloc (insertionBlock.nomeServidor, (a+1)*sizeof(char));
            insertionBlock.nomeServidor[a] = aux;
            aux = getchar();
            a++;
        }
        insertionBlock.nomeServidor = (char*) realloc (insertionBlock.nomeServidor, (a+1)*sizeof(char));
        insertionBlock.nomeServidor[a] = '\0';
        insertionBlock.tamString1 = strlen(insertionBlock.nomeServidor)+1;
        insertionBlock.tamRegistro += insertionBlock.tamString1+4+1;
    }
    getchar();  //Espaço

    //Pega o cargo e tamString2
    aux = getchar(); //Pega primeiro caractere, é obrigatoriamente " ou N
    if(aux == 'N'){
        for(a = 0; a < 3; a++)getchar(); //Pega 'ULO'
        dv2 = 1;
    }else{
        a = 0;
        aux = getchar();
        while(aux != '"' && aux != EOF && aux != '\n'){
            insertionBlock.cargoServidor = (char*) realloc (insertionBlock.cargoServidor, (a+1)*sizeof(char));
            insertionBlock.cargoServidor[a] = aux;
            aux = getchar();
            a++;
        }
        insertionBlock.cargoServidor = (char*) realloc (insertionBlock.cargoServidor, (a+1)*sizeof(char));
        insertionBlock.cargoServidor[a] = '\0';
        insertionBlock.tamString2 = strlen(insertionBlock.cargoServidor)+1;
        insertionBlock.tamRegistro += insertionBlock.tamString2+4+1;
    }


    insertionBlock.removido = '-';
    insertionBlock.encadeamentoLista = -1;

    //printf("%c %d %ld %d %.2lf %s %s ", insertionBlock.removido, insertionBlock.tamRegistro, insertionBlock.encadeamentoLista, insertionBlock.idServidor, insertionBlock.salarioServidor, insertionBlock.nomeServidor, insertionBlock.cargoServidor);
    //for(a=0; a<14; a++) printf("%c", insertionBlock.telefoneServidor[a]);
    
    //Agora que todos os dados estão alocados em insertionBlock, precisamos achar o Best-Fit, o local onde melhor se encaixa a inserção
    //Para isso percorre o arquivo, comparando todos os espaços.
    REGISTRO cabecalho = criarRegistro();
    cabecalho = lerCabecalho(bin, cabecalho);

    DATA auxBlock = createBlock();
    long int byteCounter = 32000;
    int bestFit = 999999;
    long int bestByteOffSet = 0;
    long int bestEncadeamentoLista = 0;

    while(!feof(bin)){
        auxBlock = binReadBlock(bin, auxBlock, &byteCounter);
        if(auxBlock.removido == '*' && auxBlock.tamRegistro >= insertionBlock.tamRegistro){
            if((auxBlock.tamRegistro-insertionBlock.tamRegistro) < bestFit){
                bestFit = auxBlock.tamRegistro-insertionBlock.tamRegistro;
                bestByteOffSet = byteCounter-auxBlock.tamRegistro;
                bestEncadeamentoLista = auxBlock.encadeamentoLista;
            }
        }
    }

    //Agora estão alocadas nas 3 variáveis best a quantia de lixo que vai ficar, o offset de onde será feita a inserção
    //E a posição em que EncadeamentoLista apontava, para atualizar aquele que apontava para essa posição.auxBlock
    rewind(bin);
    if(cabecalho.topoLista == bestByteOffSet){
        fseek(bin, 1, SEEK_SET);
        fwrite(&bestEncadeamentoLista, sizeof(long int), 1, bin);
    }
    else{
        //Caso o byteoffset que indica a posição que vamos ocupar não esteja no cabeçalho,
        //ela deve estar na lista, então procuramos por um registro removido que aponta o ByteOffSet do Best
        cabecalho = lerCabecalho(bin, cabecalho);
        byteCounter = 32000;
        while(!feof(bin)){
            auxBlock = binReadBlock(bin, auxBlock, &byteCounter);
            if(auxBlock.removido == '*' && auxBlock.encadeamentoLista == bestByteOffSet){
                fseek(bin, byteCounter-auxBlock.tamRegistro, SEEK_SET); //Volta para o ponto inicial do registro
                fwrite(&auxBlock.removido, sizeof(char), 1, bin);   //Copia
                fwrite(&auxBlock.tamRegistro, sizeof(int), 1, bin); //Copia
                fwrite(&bestEncadeamentoLista, sizeof(long int), 1, bin);   //Substitui o próx da lista
            }
        }
    }
    //Agora que a lista está arrumada, podemos fazer a inserção
    fseek(bin, bestByteOffSet, SEEK_SET);
    byteCounter = binWriteBlock(insertionBlock, bin, dv1, dv2, bestByteOffSet, tamAnterior);
    tamAnterior = insertionBlock.tamRegistro;

    //Está inserido o bloco
    fclose(bin);

    free(insertionBlock.telefoneServidor);
    free(insertionBlock.nomeServidor);
    free(insertionBlock.cargoServidor);
    free(auxBlock.telefoneServidor);
    free(auxBlock.nomeServidor);
    free(auxBlock.cargoServidor);
    free(str1);
    free(str2);
    free(str3);
    free(cabecalho.status);
    free(cabecalho.tagCampo1);
    free(cabecalho.tagCampo2);
    free(cabecalho.tagCampo3);
    free(cabecalho.tagCampo4);
    free(cabecalho.tagCampo5);
    free(cabecalho.desCampo1);
    free(cabecalho.desCampo2);
    free(cabecalho.desCampo3);
    free(cabecalho.desCampo4);
    free(cabecalho.desCampo5);
    free(cabecalho.preenchePaginaDisco);
}

/*
Atualiza registros em um arquivo binário
Procura registros com o critério estabelecido e substitui um dos campos
Em caso de a atualização for ficar maior que o campo, o registro é inserido ao fim da lista.
Parâmetros: Nome do arquivo
Não há retorno, mas há uma mudança no arquivo binário.
*/
void atualizarRegistro(char* fileName){

    FILE* bin = fopen(fileName, "r+b");
    
    //A primeira posição de byteOffSetList terá o número de resultados encontrados
    //As posições seguintes indica as posições dos resultados no arquivo
    //A última posição é preenchida com -1 para evitar segfault uma vez que todas as pesquisas tenham sido feitas
    long int* byteOffSetList = NULL;

    int searchIndex1 = 0, searchIndex2 = 0;
        
    searchIndex1 = definirCampo();
    byteOffSetList = pesquisar(fileName, searchIndex1, 1);
    int i = 0, j = 0;
    //for(i = 0; i < byteOffSetList[0]; i++) printf("i: %d - byteOffSet: %ld\n", i, byteOffSetList[i]);

    getchar();
    searchIndex2 = definirCampo();
    
    //Declaração de variáveis de comparação
    int idSearch = 0;
    double salarioSearch = 0;
    char* strSearch = NULL;
    strSearch = (char*) malloc (1*sizeof(char));
    char aux;

    //Entrada de dados de comparação
    //O dado entrado depende da operação que o usuário deseja fazer
    //0 pega um inteiro (id), 1 pega um double (salario), 2+ pega uma string (telefone, nome, cargo)
    if(searchIndex2 == 0) scanf("%d", &idSearch);
    if(searchIndex2 == 1) scanf("%lf", &salarioSearch);
    if(searchIndex2 > 1){
        getchar(); //Pega a primeira "
        aux = getchar();
        while(aux != '\n' && aux != '"' && aux != EOF){
            strSearch = (char*) realloc (strSearch, (i+1)*sizeof(char));
            strSearch[i] = aux;
            i++;
        }
        strSearch = (char*) realloc (strSearch, (i+1)*sizeof(char));
        strSearch[i] = '\0';
    }

    DATA block = createBlock();
    REGISTRO cabecalho = criarRegistro();
    cabecalho = lerCabecalho(bin, cabecalho);
    long int byteCounter = 32000;

    i = 0;
    while(i < byteOffSetList[0]){
        i++;
        fseek(bin, byteOffSetList[i]-byteCounter, SEEK_CUR);
        byteCounter += byteOffSetList[i]-byteCounter;
        block = binReadBlock(bin, block, &byteCounter);
        fseek(bin, byteCounter-block.tamRegistro, SEEK_SET);
        if(searchIndex2 == 0) block.idServidor = idSearch;
        if(searchIndex2 == 1) block.salarioServidor = salarioSearch;
        if(searchIndex2 == 2) strcpy(block.telefoneServidor, strSearch);
        if(searchIndex2 == 3){
            if(block.tamString1 > strlen(strSearch)){
                strSearch = (char*)realloc(strSearch, block.tamString1*sizeof(char));
                for(j = strlen(strSearch); j+1 < block.tamString1; j++){
                    strSearch[j] = '@';
                }
                strSearch[j] = '\0';
            }
        }
    }


    free(strSearch);
    free(byteOffSetList);
    free(block.telefoneServidor);
    free(block.nomeServidor);
    free(block.cargoServidor);
    free(cabecalho.status);
    free(cabecalho.tagCampo1);
    free(cabecalho.tagCampo2);
    free(cabecalho.tagCampo3);
    free(cabecalho.tagCampo4);
    free(cabecalho.tagCampo5);
    free(cabecalho.desCampo1);
    free(cabecalho.desCampo2);
    free(cabecalho.desCampo3);
    free(cabecalho.desCampo4);
    free(cabecalho.desCampo5);
    free(cabecalho.preenchePaginaDisco);
}