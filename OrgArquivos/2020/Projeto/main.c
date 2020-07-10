/*
Main do Trabalho de Organização de Arquivos

Rafael Olivier Cardoso 9436166
Leandro Sena Silva 9293060
*/

#include "cabecalho.h"
#include "registros.h"
#include "otherfunctions.h"

/*
Menu de seleção de operações:
1 - Passar dados de um arquivo csv para um arquivo binário 
2 - Leitura completa de um arquivo binário
3 - Pesquisar por campos em um arquivo binário
4 - Exibir um registro por RRN específico
5 - Remover um registro com campos específicos
6 - Inserir novo registro no fim do arquivo
7 - Atualizar registros
Outros: Sai do programa.
*/
void selecionaOperacao(){

    //Entrada do nome do arquivo a ser lido (csv para 1, bin outras)
    int opt = 0;
    scanf("%d", &opt);
    char* fileName = NULL;
    char* fileNameBin = NULL;
    getchar();
    fileName = getName();

    switch(opt){

        case 1:
            fileNameBin = getName();
            criarBin(fileName, fileNameBin);
            break;

        case 2:
            recuperarDados(fileName);
            break;

        case 3:
            pesquisar(fileName);
            break;

        case 4:
            exibirRRN(fileName);
            break;

        case 5:
            removerRegistro(fileName);
            break;

        case 6:
            inserirRegistro(fileName);
            break;

        case 7:
            //criarBin("arq03.csv", fileName);
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