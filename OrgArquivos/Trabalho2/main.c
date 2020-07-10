/*
Main do Trabalho de Organização de Arquivos

Rafael Olivier Cardoso
9436166
*/

#include "otherfunctions.h"
#include "trab1functions.h"
#include "trab2functions.h"
#include "escreverTela2.h"

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
    int searchIndex;
    int qtdRepeticao, i;

    switch(opt){
        //Criar arquivo bin com as informações em .csv
        case 1:
            fflush(stdin);
            criarBin(fileName);
            break;
        //Recupera dados em um arquivo bin
        case 2:
            fflush(stdin);
            recuperarDados(fileName);
            break;
        //Pesquisa em um arquivo bin com um critério 
        case 3:
            fflush(stdin);
            searchIndex = definirCampo();
            pesquisar(fileName, searchIndex, 0);
            break;
        case 4:
            //Algumas estruturas para teste foram deixadas para facilitar o teste do programa
            criarBin("trabalho1-BCC-dados.csv");
            fflush(stdin);
            scanf("%d", &qtdRepeticao);
            for(i = 0; i < qtdRepeticao; i++){
                fflush(stdin);
                getchar();
                getchar();
                removerRegistro(fileName);
            }
            recuperarDados(fileName);
            //binarioNaTela2(fileName);
            break;
        case 5:
            //Algumas estruturas para teste foram deixadas para facilitar o teste do programa
            /*criarBin("trabalho1-BCC-dados.csv");
            scanf("%d", &qtdRepeticao);
            for(i = 0; i < qtdRepeticao; i++){
                getchar();
                removerRegistro(fileName);
            }
            getchar();*/
            fflush(stdin);
            scanf("%d", &qtdRepeticao);
            for(i = 0; i < qtdRepeticao; i++){
                getchar();
                fflush(stdin);
                inserirRegistro(fileName);
            }
            //recuperarDados(fileName);
            binarioNaTela2(fileName);
            break;
        case 6:
            fflush(stdin); 
            scanf("%d", &qtdRepeticao);
            for(i = 0; i < qtdRepeticao; i++){
                getchar();
                fflush(stdin);
                atualizarRegistro(fileName);
            }
            
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