/*
Funções para pesquisar registros com dados específicos

Rafael Olivier Cardoso
9436166
*/

#include "pesquisa.h"
#include "register.h"

/*
Função para impressão de um cabeçalho, com indicador de quais campos imprimir.
Parâmetros: Registro cabeçalho, vetor de inteiros (booleanos) com a validade de cada campo.
Não há retorno.
*/
void printCabecalho(REGISTRO reg, int* campoValido){
    printf("numero de identificacao do servidor: ");
    printf("%s\n", reg.desCampo1);

    printf("salario do servidor: ");
    if(campoValido[1] == 1) printf("%s\n", reg.desCampo2);
    else printf("valor nao declarado\n");

    printf("telefone celular do servidor: ");
    if(campoValido[2] == 1) printf("%s\n", reg.desCampo3);
    else printf("valor nao declarado\n");

    printf("nome do servidor: ");
    if(campoValido[3] == 1) printf("%s\n", reg.desCampo4);
    else printf("valor nao declarado\n");

    printf("cargo do servidor: ");
    if(campoValido[4] == 1 && reg.desCampo5[1] != '@') printf("%s\n", reg.desCampo5);
    else printf("valor nao declarado\n");

    printf("\n");
}

/*
Função para pesquisar campos dentro de um arquivo binário
Pelo seu tamanho, os detalhes de seu funcionamento serão dados dentro da função.
Campos: 0 - id, 1 - salario, 2 - telefone, 3 - nome, 4 - cargo
Parâmetros: Nome do arquivo bin (ex: "arquivo.bin"), número do campo a ser pesquisado.
Não há retorno.
*/
void pesquisar(char* fileName, int searchIndex){

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
        char aux;
        aux = getchar();
        while(aux != '\n' && aux != EOF){
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

    if(fileBIN == NULL) printf("Falha no processamento do arquivo.");
    else{
        int dataFound = 0;  //Indica se algo foi achado 0 = false, 1 = true
        char removido, fill;    //Opera páginas de disco
        int byteCounter = 0, numPaginas = 1; //Checa páginas de disco
        int tamRegistro = 0, lineCounter = 0; //Indica o tamanho de cada registro
        long int encadeamentoLista; //Não será usado nesse trabalho
        int idServidor = 0; //Será comparado com o procurado
        double salarioServidor = 0; //Será comparado com o procurado
        char* telefoneServidor = NULL; //Será comparado com o procurado
        telefoneServidor = (char*) calloc (14, sizeof(char));
        char* nomeServidor = NULL; //Será comparado com o procurado
        char* cargoServidor = NULL; //Será comparado com o procurado
        int tamString1 = 0, tamString2 = 0; //Indica tamanho dos campos variáveis
        char delimCampo4 = '|', delimCampo5 = '|';  //Delimitador dos campos variáveis
        int* campoValido = NULL;    //String para indicar quais campos contém dados para impressao
        
        //Set de campoValido
        campoValido = (int*) malloc (5*sizeof(int));
        for(a = 0; a<5; a++) campoValido[a] = 0;

        //Rotina de busca
        while(!feof(fileBIN)){

            //Pega removido e checa se chegou ao fim de uma página de disco
            fread(&removido, sizeof(char), 1, fileBIN);
            if(removido == '@'){
                fill = removido;
                while(fill == '@'){
                    fread(&fill, sizeof(char), 1, fileBIN);
                }
                byteCounter = 0;
                numPaginas++;
            }

            //Leitura do tamanho e incremento de byteCounter
            fread(&tamRegistro, sizeof(int), 1, fileBIN);
            byteCounter += tamRegistro;

            //Leituras dos outros campos fixos
            fread(&encadeamentoLista, sizeof(long int), 1, fileBIN);
            //Le e grava o id
            fread(&idServidor, sizeof(int), 1, fileBIN);
            sprintf(reg.desCampo1, "%d", idServidor);

            //le e grava o salário
            fread(&salarioServidor, sizeof(double), 1, fileBIN);
            if(salarioServidor == -1) campoValido[1] = 0;
            else{
                campoValido[1] = 1;
                sprintf(reg.desCampo2, "%.2lf", salarioServidor);
            }

            //le e grava o telefone
            fread(telefoneServidor, sizeof(char), 14, fileBIN);
            if(telefoneServidor[0] == '\0') campoValido[2] = 0;
            else{
                campoValido[2] = 1;
                for(a = 0; a < 14; a++) reg.desCampo3[a] = telefoneServidor[a];
                reg.desCampo3[a] = '\0';
            }
            lineCounter = 39;

            //Le e grava os campos variáveis
            if(lineCounter < tamRegistro){
                fread(&tamString1, sizeof(int), 1, fileBIN);
                fread(&delimCampo4, sizeof(char), 1, fileBIN);
                nomeServidor = (char*) realloc (nomeServidor, tamString1*sizeof(char*));
                fread(nomeServidor, sizeof(char), tamString1, fileBIN);

                if(tamString1 < 40 && nomeServidor != NULL){
                    campoValido[3] = 1;
                    strcpy(reg.desCampo4, nomeServidor);
                }

                //verifica a existencia do proximo campo variavel
                lineCounter += tamString1;
                lineCounter += 6;
                if(lineCounter < tamRegistro){
                    fread(&tamString2, sizeof(int), 1, fileBIN);
                    fread(&delimCampo5, sizeof(char), 1, fileBIN);
                    cargoServidor = (char*) realloc (cargoServidor, (tamString2)*sizeof(char*));
                    fread(cargoServidor, sizeof(char), tamString2, fileBIN);

                    if(tamString2 < 40 && tamString2 > 0){
                        campoValido[4] = 1;
                        strcpy(reg.desCampo5, cargoServidor);
                    }
                }
            }

            //Chamada de funções para impressão caso tenha sido encontrada semelhança
            if(searchIndex == 0 && idSearch == idServidor){
                printCabecalho(reg, campoValido);
                dataFound = 1;
            }
            if(searchIndex == 1 && salarioSearch == salarioServidor){
                printCabecalho(reg, campoValido);
                dataFound = 1;
            }
            if(searchIndex == 2 && strcmp(strSearch, reg.desCampo3) == 0){
                printCabecalho(reg, campoValido);
                dataFound = 1;
            }
            if(searchIndex == 3 && strcmp(strSearch, reg.desCampo4) == 0){
                printCabecalho(reg, campoValido);
                dataFound = 1;
            }
            if(searchIndex == 4 && strcmp(strSearch, reg.desCampo5) == 0){
                printCabecalho(reg, campoValido);
                dataFound = 1;
            }

            //Zerar dados para a próxima entrada
            reg = zerarRegistro(reg);
            for(a = 0; a<5; a++) campoValido[a] = 0;
        }

        //Imprime as páginas de disco se a pesquisa foi bem sucedida ou avisa da inexistência do registro.
        if(dataFound == 1) printf("Número de páginas de disco acessadas: %d\n", numPaginas);
        else printf("Registro Inexistente.");

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

        free(telefoneServidor);
        free(nomeServidor);
        free(cargoServidor);
        free(campoValido);

    }

    //Libera strSearch caso a pesquisa tenha sido por uma string
    if(searchIndex > 1) free(strSearch);
}