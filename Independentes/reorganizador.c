/*
Filtrador de Arquivos.
Seleciona entre n arquivos 001.pdf, 002.pdf ... e apaga o restante, reordenando o resto.

Rafael Olivier Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* adicionarPDF(char* str){    
    str[3] = '.';
    str[4] = 'p';
    str[5] = 'd';
    str[6] = 'f';
    str[7] = '\0';

    return str;
}

char* incrementarNumero(char* nome){

    if(nome[2] != '9') nome[2]++;
    else{
        nome[2] = '0';
        if(nome[1] != '9')nome[1]++;
        else{
            nome[1] = '0';
            if(nome[0] != '9') nome[0]++;
            else{
                printf("Máximo de 999 arquivos atingido!");
                exit(1);
            }
        }
    }

    nome = adicionarPDF(nome);

    return nome;
}

int main(void){

    int qtd = 0, a, counter = 0;

    char* nomeArquivo = NULL;
    nomeArquivo = (char*) calloc (100, sizeof(char));
    nomeArquivo = adicionarPDF(nomeArquivo);

    char* nomeProximo = NULL;
    nomeProximo = (char*) calloc (4, sizeof(char));
    for(a = 0; a < 3; a++) nomeProximo[a] = '0';
    nomeProximo = adicionarPDF(nomeProximo);

    char* novoNome = NULL;
    novoNome = (char*) calloc (4, sizeof(char));
    for(a = 0; a < 3; a++) novoNome[a] = '0';
    novoNome = adicionarPDF(novoNome);

    //Necessario para apagar arquivos maiores do que o último mantido
    printf("Digite o maior número de arquivo da pasta. Ex: 093\nNão coloque nada além dos números!\n");
    scanf("%s", nomeArquivo);
    qtd = atoi(nomeArquivo);
    if(qtd == 0){
        printf("Número inválido. Você tem certeza que colocou só números? Programa encerrando...\n");
        exit(1);
    }
    
    //Processamento
    printf("Digite os números dos arquivos que deseja manter, coloque a letra S no final e em seguinda ENTER.\n");
    printf("Os arquivos não especificados serão apagados!\n");
    printf("Ex: 001 003 005 006 007 032 S\n");
    
    scanf("%s", nomeArquivo);
    nomeArquivo = adicionarPDF(nomeArquivo);

    while(nomeArquivo[0] != 'S'){
        counter++;
        nomeProximo = incrementarNumero(nomeProximo);
        printf("nomeProximo: %s\n", nomeProximo);
        printf("nomeArquivo: %s\n", nomeArquivo);
        printf("novoNome: %s\n", novoNome);

        if(strcmp(nomeProximo, nomeArquivo) == 0){
            novoNome = incrementarNumero(novoNome);
            rename(nomeArquivo, novoNome);
            scanf("%s", nomeArquivo);
            nomeArquivo = adicionarPDF(nomeArquivo);
        }else remove(nomeProximo);
    }

    for(a = counter; a < qtd; a++){
        nomeProximo = incrementarNumero(nomeProximo);
        remove(nomeProximo);
    }


    free(nomeArquivo);
    free(nomeProximo);

    return 0;
}