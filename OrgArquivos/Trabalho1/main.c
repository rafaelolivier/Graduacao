/*
Main do Trabalho 1 de Organização de Arquivos

Rafael Olivier Cardoso
9436166
*/

#include "register.h"
#include "pesquisa.h"
#include "t2func.h"

/*
Função para pegar uma string na entrada padrão.
Aloca 40 bytes de memória, pois nenhum nome passa desse tamanho.
Não há parâmetros.
Retorna uma string com \0 no final.
*/
char* getName(){

    char* name;
    char aux;

    name = (char*)malloc(40*sizeof(char));
    int i = 0;
    aux = getchar();
    while(aux != ' ' && aux != '\n' && aux != EOF){
        name[i] = aux;
        i++;
        aux = getchar();
    }
    name[i] = '\0';

    return name;
}

/*
Função para copiar os dados de um arquivo CSV para um Binário
Pelo seu tamanho, os detalhes de seu funcionamento serão dados dentro da função.
Parâmetros: Nome do arquivo csv (ex: "arquivo.csv")
Não há retorno.
*/
void criarBin(char* fileName){

    //Abrir arquivos csv e binário
    FILE *fileCSV;
    FILE *fileBIN;

    fileCSV = fopen(fileName, "r");
    fileBIN = fopen("arquivoTrab1.bin", "w+b");

    //Checagem de existência do arquivo
    if(fileCSV == NULL) printf("Falha no processamento do arquivo.");
    else{
        
        char* line = NULL;
        char* str = NULL;
        line = (char*) calloc (300, sizeof(char));
        str = (char*) calloc (40, sizeof(char)); 
        //Assumime-se que o número maximo de caracteres nos campos variáveis é 40.
        //A Primeira linha do arquivo é um cabeçalho e não precisa ser colocado no .bin
        fgets(line, 300, fileCSV);

        //Declarações de contadores e variáveis para ler e armazenar no binário
        int a = 0;
        int byteCounter = 0;    //Conta quantos bytes já foram lidos e inseridos
        int idServidor = 0;     //Grava o id do servidor
        double salarioServidor = 0.0;   //grava o salário do servidor
        char* telefoneServidor = NULL;  //grava o telefone do servidor
        telefoneServidor = (char*) calloc (14, sizeof(char)); //Não terá \0, exige cuidado na manipulação
        char* nomeServidor = NULL;  //grava o nome do servidor
        char* cargoServidor = NULL; //grava o cargo do servidor
        int tamString1 = 0, tamString2 = 0, tamRegistro= 0; //grava o tamanho do nome, cargo e do registro
        char removido = '-';    //Não será usado nesse primeiro trabalho prático, mas deve ser inserido no arquivo
        long int encadeamentoLista = -1;    //Como em "removido"
        char delimCampo4 = '|', delimCampo5 = '|';  //Grava os delimitadores dos campos variáveis

        //Variáveis para tratamento de campos vazios
        int vcounter = 0; //contador de virgulas
        int dv = 0; //Boolean para definir se há campos vazios (0 false | 1 true)
        int* empty = NULL;  //Marca quais campos estão vazios
        empty = (int*) malloc (6*sizeof(int));

        //Contador de linhas
        int entryCounter = 0;   //Numero de registros
        char ch;    //Auxiliar
        while(!feof(fileCSV)){
            ch = getc(fileCSV);
            if(ch == '\n') entryCounter++;
        }
        rewind(fileCSV);
        //Como voltamos ao inicio do arquivo, devemos pular a primeira linha novamente
        fgets(line, 300, fileCSV);

        for(;entryCounter > 0; entryCounter--){ //Repete uma vez por registro
            
            //Formatação do registro e tratamento de campos vazios
            fgets(line, 300, fileCSV);
            tamRegistro = 0;
            vcounter = 0;
            dv = 0;
            for(a = 0; a < 6; a++) empty[a] = 0;
            a = 0;

            //Verificar se há campos vazios para tratamento
            while(line[a] != '\0'){
                if(line[a] == ','){
                    vcounter++;
                    if(line[a+1] == ','){
                        dv = 1;
                        empty[vcounter] = 1;
                    }
                }
                a++;
            }

            //Inicio da transferência de dados
            //A função strtok transforma as strings separadas por virgulas em tokens
            //Primeiro pegamos os campos fixos
            //Transferência do campo idServidor
            str = strtok(line, ",");
            idServidor = atoi(str);

            //Transferência do campo salarioServidor
            if(dv != 1 || empty[1] != 1){
                str = strtok(NULL, ",");
                salarioServidor = atof(str);
            }else{
                salarioServidor = -1;
            }

            //Transferência do campo telefoneServidor
            if(dv != 1 || empty[2] != 1){
                str = strtok(NULL, ",");
                for(a = 0; a < 14; a++) telefoneServidor[a] = str[a];
            }else{
                telefoneServidor[0] = '\0';
                for(a = 1; a < 14; a++) telefoneServidor[a] = '@';
            }
            tamRegistro = 39;   
            //39 bytes = 26 (campos fixos) + 1 (removido) + 4(tamanho) + 8(encadeamentoLista)

            //Agora os campos variáveis
            //Transferência do campo nomeServidor
            if(dv != 1 || empty[3] != 1){
                str = strtok(NULL, ",");
                tamString1 = strlen(str)+1;
                nomeServidor = (char*) realloc (nomeServidor, 1+(tamString1*sizeof(char)));
                strcpy(nomeServidor, str);
                nomeServidor[tamString1-1] = '\0';
                tamRegistro += tamString1 + 4 + 1;
                //tamRegistro +=  strlen + 4 tamanho do campo variáveis + 1 (tags c4);
            }

            //Transferência do campo cargoServidor
            if(dv != 1 || empty[4] != 1){
                str = strtok(NULL, ",");
                tamString2 = strlen(str);
                cargoServidor = (char*) realloc (cargoServidor, 1+(tamString2*sizeof(char)));
                strcpy(cargoServidor, str);
                cargoServidor[tamString2-1] = '\0';
                tamRegistro += tamString2 + 4 + 1;
            }
            char fill = '@';

            //Escrever no .bin
            //Verificação se o registro caberá na página de disco, antes de gravar
            if(tamRegistro + byteCounter <= 32000){
                byteCounter += tamRegistro;
            }else{
                //Essa página de disco não terá espaço suficiente, preencha com '@'
                for(a = 32000-byteCounter; a > 0; a--) fwrite(&fill, sizeof(char), 1, fileBIN);
                byteCounter = 0;
            }

            //Bloco de chamadas de fwrite, onde os registros serão de fato escritos no binário
            //Os campos de tamanho variável só escrevem se não forem nulos
            fwrite(&removido, sizeof(char), 1, fileBIN);
            fwrite(&tamRegistro, sizeof(int), 1, fileBIN);
            fwrite(&encadeamentoLista, sizeof(long int), 1, fileBIN);
            fwrite(&idServidor, sizeof(int), 1, fileBIN);
            fwrite(&salarioServidor, sizeof(double), 1, fileBIN);
            fwrite(telefoneServidor, sizeof(char), 14, fileBIN);
            if(dv != 1 || empty[3] != 1){
                fwrite(&tamString1, sizeof(int), 1, fileBIN);
                fwrite(&delimCampo4, sizeof(char), 1, fileBIN);
                fwrite(nomeServidor, sizeof(char), tamString1, fileBIN);
            }
            if(dv != 1 || empty[4] != 1){
                fwrite(&tamString2, sizeof(int), 1, fileBIN);
                fwrite(&delimCampo5, sizeof(char), 1, fileBIN);
                fwrite(cargoServidor, sizeof(char), tamString2, fileBIN);
            }
        }

        //Liberação de memório, fechamento de arquivos, impressão de mensagem de saída.
        free(empty);
        free(line);
        free(telefoneServidor);
        free(nomeServidor);
        free(cargoServidor);

        fclose(fileBIN);
        fclose(fileCSV);

        printf("%s\n", "arquivoTrab1.bin");
    }
}

/*
Função para copiar os dados de um arquivo binário para a saída padrão.
Pelo seu tamanho, os detalhes de seu funcionamento serão dados dentro da função.
Parâmetros: Nome do arquivo bin (ex: "arquivo.bin")
Não há retorno.
*/
void recuperarDados(char* name){

    //Abrir arquivo para leitura
    FILE* fileBIN;
    fileBIN = fopen(name, "rb");

    //Checagem de existência do arquivo
    if(fileBIN == NULL) printf("Registro inexistente.");
    else{

        //Contadores e variáveis de armazenamento
        int a = 0;
        int byteCounter = 0;    //Grava a quantia de bytes utilizada
        int idServidor = 0;     //Grava o id do servidor
        double salarioServidor = 0.0;   //Grava o salario do Servidor
        char* telefoneServidor = NULL;  //Grava o telefone do Servidor
        telefoneServidor = (char*) calloc (14, sizeof(char)); //Não terá \0, exige cuidado na manipulação
        char* nomeServidor = NULL;  //Grava o nome do servidor
        char* cargoServidor = NULL; //Grava o cargo do servidor
        int tamString1 = 0, tamString2 = 0, tamRegistro= 0; //Tamanho dos campos variáveis e do registro
        char removido = '-';    //Não será utilizado nesse trabalho, mas deve ser lido para a operação ter sucesso
        char delimCampo4 = '|', delimCampo5 = '|';  //Marca o inicio dos campos variáveis
        long int encadeamentoLista = -1;    //Como em "removido"
        char fill;  //Tratamento das páginas de disco preenchidas com @
        int numPaginas = 1; //Contador do num de paginas

        //Controle de campos vazios
        int lineCounter = 0;
        int print1= 0, print2 = 0; //Booleans para indicar se os campos variáveis estão vazios

        //Ler as linhas de bins
        while(!feof(fileBIN)){

            //reset
            print1 = 0;
            print2 = 0;

            //Começa a leitura
            fread(&removido, sizeof(char), 1, fileBIN);
            //Verifica se chegou ao último registro da página de disco
            if(removido == '@'){
                fill = removido;
                while(fill == '@'){
                    fread(&fill, sizeof(char), 1, fileBIN);
                }
                byteCounter = 0;
                numPaginas++;
                removido = fill;
            }

            //Leitura do tamanho e incremento de byteCounter
            fread(&tamRegistro, sizeof(int), 1, fileBIN);
            byteCounter += tamRegistro;

            //Leituras dos outros campos fixos
            fread(&encadeamentoLista, sizeof(long int), 1, fileBIN);
            fread(&idServidor, sizeof(int), 1, fileBIN);
            fread(&salarioServidor, sizeof(double), 1, fileBIN);
            fread(telefoneServidor, sizeof(char), 14, fileBIN);
            lineCounter = 39;

            //Leitura dos campos variáveis
            if(lineCounter < tamRegistro){
                fread(&tamString1, sizeof(int), 1, fileBIN);
                fread(&delimCampo4, sizeof(char), 1, fileBIN);
                nomeServidor = (char*) realloc (nomeServidor, tamString1*sizeof(char*));
                fread(nomeServidor, sizeof(char), tamString1, fileBIN);

                //Set de um campo variável e verifica a existencia do proximo campo variavel
                print1 = 1;
                lineCounter += tamString1;
                lineCounter += 6;

                //Leitura do segundo campo variável
                if(lineCounter < tamRegistro){
                    fread(&tamString2, sizeof(int), 1, fileBIN);
                    fread(&delimCampo5, sizeof(char), 1, fileBIN);
                    cargoServidor = (char*) realloc (cargoServidor, tamString2*sizeof(char*));
                    fread(cargoServidor, sizeof(char), tamString2, fileBIN);
                    //Seta a existencia do segundo campo variável
                    print2 = 1;
                }
            }

            //Impressões do registro
            printf("%d %.2lf ", idServidor, salarioServidor);
            for(a = 0; a < 14; a++) printf("%c", telefoneServidor[a]);
            if(print1 = 1) printf(" %d %s", tamString1-1, nomeServidor);
            if(print2 = 1) printf(" %d %s", tamString2-1, cargoServidor);
            printf("\n");
        }

        //Impressão do número de páginas de disco e liberação de memória
        printf("Número de páginas de disco acessadas: %d\n", numPaginas);

        fclose(fileBIN);

        free(telefoneServidor);
        free(nomeServidor);
        free(cargoServidor);
    }
}

/*
Função organizar a pesquisa no arquivo binário.
Passa para a função principal os parâmetros inseridos pelo usuário
Parâmetros: Nome do arquivo csv (ex: "arquivo.bin")
Não há retorno.
*/
void pesquisarRegistro(char* fileName){
    //A operação depende do tipo de dado que o usuário deseja pesquisar
    char* nomeDoCampo;
    nomeDoCampo = getName();

    //Os campos podem ser: 
    //  "idServidor", "salarioServidor", "telefoneServidor", "nomeServidor" e "cargoServidor"
    //Como todos eles tem letras iniciais diferentes, será usada uma operação de Switch com char
    char op = nomeDoCampo[0];
    switch (op){
        case 'i':
        pesquisar(fileName, 0);
        break;
        case 's':
        pesquisar(fileName, 1);
        break;
        case 't':
        pesquisar(fileName, 2);
        break;
        case 'n':
        pesquisar(fileName, 3);
        break;
        case 'c':
        pesquisar(fileName, 4);
        break;
    }

    free(nomeDoCampo);
}


/*
Menu de seleção de operações:
1 - Passar dados de um arquivo csv para um arquivo binário 
2 - Leitura completa de um arquivo binário
3 - Procura de registros em um arquivo binário
*/
void selecionaOperacao(){

    //Entrada do nome do arquivo a ser lido (csv para 1, bin para 2 e 3)
    int opt = 0;
    scanf("%d", &opt);
    char* fileName = NULL;
    getchar();
    fileName = getName();

    switch(opt){
        //Criar arquivo bin com as informações em .csv
        case 1:
            criarBin(fileName);
            break;
        //Recupera dados em um arquivo bin
        case 2:
            recuperarDados(fileName);
            break;
        //Pesquisa em um arquivo bin com um critério 
        case 3:
            pesquisarRegistro(fileName);
            break;
        case 4:
            removerRegistro(fileName);
            break;
        case 5:
            inserirRegistro(fileName);
            break;
        case 6:
            atualizarRegistro(fileName);
            break;
    }

    free(fileName);
}


int main (void){

    //Inicia operações e seta linguagem para português
    setlocale(LC_ALL, "Portuguese");
    selecionaOperacao();

    return 0;
}