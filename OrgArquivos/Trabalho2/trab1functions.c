#include "trab1functions.h"

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
        
        //Contador de linhas
        int entryCounter = -1;   //Numero de registros
        char ch;    //Auxiliar
        while(!feof(fileCSV)){
            ch = getc(fileCSV);
            if(ch == '\n') entryCounter++;
        }
        rewind(fileCSV);

        REGISTRO cabecalho;
        cabecalho = criarRegistro();
        cabecalho = getCabecalhoCSV(fileCSV, cabecalho);
        escreverCabecalho(fileBIN, cabecalho);

        char* line = NULL;
        line = (char*) calloc (300, sizeof(char));
        char* str = NULL;
        str = (char*) calloc (40, sizeof(char)); 
        //Assumime-se que o número maximo de caracteres nos campos variáveis é 40.

        long int byteCounter = 0;    //Conta quantos bytes já foram lidos e inseridos
        int tamAnterior = 0;
        int a = 0;
        DATA entry = createBlock();

        //Variáveis para tratamento de campos vazios
        int vcounter = 0; //contador de virgulas
        int dv = 0; //Boolean para definir se há campos vazios (0 false | 1 true)
        int* empty = NULL;  //Marca quais campos estão vazios
        empty = (int*) malloc (6*sizeof(int));

        for(;entryCounter > 0; entryCounter--){ //Repete uma vez por registro
            
            //Formatação do registro e tratamento de campos vazios
            fgets(line, 300, fileCSV);
            entry.tamRegistro = 0;
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
            //Transferência do campo entry.idServidor
            str = strtok(line, ",");
            entry.idServidor = atoi(str);

            //Transferência do campo entry.salarioServidor
            if(dv != 1 || empty[1] != 1){
                str = strtok(NULL, ",");
                entry.salarioServidor = atof(str);
            }else{
                entry.salarioServidor = -1;
            }

            //Transferência do campo entry.telefoneServidor
            if(dv != 1 || empty[2] != 1){
                str = strtok(NULL, ",");
                for(a = 0; a < 14; a++) entry.telefoneServidor[a] = str[a];
            }else{
                entry.telefoneServidor[0] = '\0';
                for(a = 1; a < 14; a++) entry.telefoneServidor[a] = '@';
            }
            entry.tamRegistro = 34;   
            //34 = tamanho dos campos fixos

            //Agora os campos variáveis
            //Transferência do campo entry.nomeServidor
            if(dv != 1 || empty[3] != 1){
                str = strtok(NULL, ",");
                entry.tamString1 = strlen(str)+1;
                entry.nomeServidor = (char*) realloc (entry.nomeServidor, 1+(entry.tamString1*sizeof(char)));
                strcpy(entry.nomeServidor, str);
                entry.nomeServidor[entry.tamString1-1] = '\0';
                entry.tamRegistro += entry.tamString1 + 4 + 1;
                //entry.tamRegistro +=  strlen + 4 tamanho do campo variáveis + 1 (tags c4);
                entry.tamString1++;
            }
            //Transferência do campo entry.cargoServidor
            if(dv != 1 || empty[4] != 1){
                str = strtok(NULL, ",");
                entry.tamString2 = strlen(str);
                entry.cargoServidor = (char*) realloc (entry.cargoServidor, 1+(entry.tamString2*sizeof(char)));
                strcpy(entry.cargoServidor, str);
                entry.cargoServidor[entry.tamString2-1] = '\0';
                entry.tamRegistro += entry.tamString2 + 4 + 1;
                entry.tamString2++;
            }

            byteCounter = binWriteBlock(entry, fileBIN, empty[3], empty[4], byteCounter, tamAnterior);
            tamAnterior = entry.tamRegistro;
        }

        //Liberação de memório, fechamento de arquivos, impressão de mensagem de saída.
        free(empty);
        free(line);
        free(entry.telefoneServidor);
        free(entry.nomeServidor);
        free(entry.cargoServidor);

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

        REGISTRO cabecalho;
        cabecalho = criarRegistro();
        cabecalho = lerCabecalho(fileBIN, cabecalho);
        printf("topoLista: %ld\n", cabecalho.topoLista);

        //Contadores e variáveis de armazenamento
        int a = 0;
        long int byteCounter = 32000;
        DATA block = createBlock();

        //Ler as linhas de bins
        while(!feof(fileBIN)){

            block = binReadBlock(fileBIN, block, &byteCounter);

            if(!feof(fileBIN)){
                if(block.removido != '*'){
                    //Impressões do registro
                    printf("%d ", block.idServidor);
                    if(block.salarioServidor != -1) printf("%.2lf ", block.salarioServidor);
                    else printf("         ");
                    if(block.telefoneServidor[1] != '@') for(a = 0; a < 14; a++) printf("%c", block.telefoneServidor[a]);
                    else for(a = 0; a < 14; a++) printf(" ");
                    if(block.delimCampo4 != 'v') printf(" %d %s", block.tamString1-2, block.nomeServidor);
                    if(block.delimCampo5 != 'v') printf(" %d %s", block.tamString2-2, block.cargoServidor);
                    printf("\n");
                }
                else printf("ArquivoRemovido. ByteOffSet: %ld RRN: %ld\n", byteCounter-block.tamRegistro-5, block.encadeamentoLista);
            }
        }

        //Impressão do número de páginas de disco e liberação de memória

        int numPaginas = (int)byteCounter/32000;
        numPaginas += 2;
        printf("Número de páginas de disco acessadas: %d\n", numPaginas);

        fclose(fileBIN);

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
}

/*
Função para pesquisar campos dentro de um arquivo binário
Pelo seu tamanho, os detalhes de seu funcionamento serão dados dentro da função.
Campos: 0 - id, 1 - salario, 2 - telefone, 3 - nome, 4 - cargo
Parâmetros: Nome do arquivo bin (ex: "arquivo.bin"), número do campo a ser pesquisado, boolean: remove (é uma remoção?)
Não há retorno.
*/
long int* pesquisar(char* fileName, int searchIndex, int remove){

    //Abertura do arquivo para leitura
    FILE* fileBIN;
    fileBIN = fopen(fileName, "rb");

    //Declaração de variáveis de comparação
    int idSearch = 0;
    double salarioSearch = 0;
    char* strSearch = NULL;
    
    int a = 0;  //Contador

    //Entrada de dados de comparação
    //O dado entrado depende da operação que o usuário deseja fazer
    //0 pega um inteiro (id), 1 pega um double (salario), 2+ pega uma string (telefone, nome, cargo)
    if(searchIndex == 0) scanf("%d", &idSearch);
    if(searchIndex == 1) scanf("%lf", &salarioSearch);

    if(searchIndex > 1){
        if(remove == 1 && searchIndex > 1) getchar(); //Pega a primeira "
        char aux;
        aux = getchar();
        while(aux != '\n' && aux != '"' && aux != EOF){
            strSearch = (char*) realloc (strSearch, (a+1)*sizeof(char));
            strSearch[a] = aux;
            a++;
            aux = getchar();
        }
        strSearch = (char*) realloc (strSearch, (a+1)*sizeof(char));
        strSearch[a] = '\0';
    }

    //Cria registro para usar para impressão
    REGISTRO reg = criarRegistro();
    //Cria registro para leitura de cabecalho
    REGISTRO cabecalho;
    cabecalho = criarRegistro();
    cabecalho = lerCabecalho(fileBIN, cabecalho);

    if(fileBIN == NULL) printf("Falha no processamento do arquivo.");
    else{

        DATA block = createBlock();        

        //Variáveis para a remoção do trabalho 2
        int nRegistrosFound = 1;
        long int* byteOffSetList = NULL;
        int pos = 0;
        
        //Set de campoValido
        int* campoValido = NULL;
        campoValido = (int*) malloc (5*sizeof(int));
        for(a = 0; a<5; a++) campoValido[a] = 0;
        long int byteCounter = 32000;

        int dataFound = 0;
        int dataFoundTrue = 0;

        //Rotina de busca
        while(!feof(fileBIN)){

            block = binReadBlock(fileBIN, block, &byteCounter);

            if(!feof(fileBIN)){
                sprintf(reg.desCampo1, "%d", block.idServidor);
                if(block.salarioServidor == -1) campoValido[1] = 0;
                else{
                    campoValido[1] = 1;
                    sprintf(reg.desCampo2, "%.2lf", block.salarioServidor);
                }
                if(block.telefoneServidor[0] == '\0') campoValido[2] = 0;
                else{
                    campoValido[2] = 1;
                    for(a = 0; a < 14; a++) reg.desCampo3[a] = block.telefoneServidor[a];
                    reg.desCampo3[a] = '\0';
                }
                if(block.tamString1 < 40 && block.nomeServidor != NULL){
                    campoValido[3] = 1;
                    strcpy(reg.desCampo4, block.nomeServidor);
                }
                if(block.tamString2 < 40 && block.tamString2 > 0 && block.cargoServidor != NULL){
                    campoValido[4] = 1;
                    strcpy(reg.desCampo5, block.cargoServidor);
                }

                //Seta boolean caso tenha encontrado semelhança
                if(searchIndex == 0 && idSearch == block.idServidor) dataFound = 1;
                if(searchIndex == 1 && salarioSearch == block.salarioServidor) dataFound = 1;
                if(searchIndex == 2 && strcmp(strSearch, reg.desCampo3) == 0) dataFound = 1;
                if(searchIndex == 3 && strcmp(strSearch, reg.desCampo4) == 0) dataFound = 1;
                if(searchIndex == 4 && strcmp(strSearch, reg.desCampo5) == 0) dataFound = 1;

                //Caso encontrado, dependendo se a intenção é remover ou imprimir, mudam as instruções
                if(dataFound == 1){
                    dataFound = 0;
                    dataFoundTrue = 1;
                    if(remove == 1){
                        nRegistrosFound++;
                        byteOffSetList = (long int*) realloc (byteOffSetList, nRegistrosFound*sizeof(long int));
                        pos = byteCounter;
                        pos = pos-(block.tamRegistro+5);
                        byteOffSetList[nRegistrosFound-1] = pos;
                    }
                    else printCabecalho(reg, campoValido);
                }

                //Zerar dados para a próxima entrada
                reg = zerarRegistro(reg);
                for(a = 0; a<5; a++) campoValido[a] = 0;
            }
        }

        //Libera memória e fecha arquivo
        fclose(fileBIN);

        free(reg.status);
        free(reg.tagCampo1);
        free(reg.tagCampo2);
        free(reg.tagCampo3);
        free(reg.tagCampo4);
        free(reg.tagCampo5);
        free(reg.desCampo1);
        free(reg.desCampo2);
        free(reg.desCampo3);
        free(reg.desCampo4);
        free(reg.desCampo5);
        free(reg.preenchePaginaDisco);

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

        free(block.telefoneServidor);
        free(block.nomeServidor);
        free(block.cargoServidor);
        free(campoValido);
        if(searchIndex > 1) free(strSearch);

        if(remove != 1){
            int numPaginas = 1;
            numPaginas += (int)byteCounter/32000;

            //Imprime as páginas de disco se a pesquisa foi bem sucedida ou avisa da inexistência do registro.
            if(dataFoundTrue == 1) printf("Número de páginas de disco acessadas: %d\n", numPaginas);
            else printf("Registro inexistente.");
        }else{
            byteOffSetList = (long int*) realloc (byteOffSetList, (nRegistrosFound+1)*sizeof(long int));
            byteOffSetList[0] = nRegistrosFound-1;
            byteOffSetList[nRegistrosFound] = -1;
            return byteOffSetList;
        }
    }

    //Libera strSearch caso a pesquisa tenha sido por uma string
    if(searchIndex > 2) free(strSearch);
}