/*
Removedor de quebra de linha de txt
Rafael Olivier Cardoso
*/

#include <stdio.h>
#include <stdlib.h>

void atualizaArquivo(char* nomeArquivo){
    FILE* oldFile;
    FILE* newFile;
    char c;

    oldFile = fopen(nomeArquivo, "r");
    newFile = fopen("newFile", "w");

    c = fgetc(oldFile);
    while(!feof(oldFile)){
        if(c != '\n'){
            fputc(c, newFile);
        }
        c = fgetc(oldFile);
    }

    fclose(oldFile);
    fclose(newFile);

    rename(nomeArquivo, "delete");
    rename("newFile", nomeArquivo);
    remove("delete");
}


int main (void){

    printf("Insira o nome do arquivo que deseja apagar todas as quebras de linha. Ex: arquivo.txt\n");
    char* nomeArquivo;
    nomeArquivo = (char*)calloc(50, sizeof(char));

    scanf("%s", nomeArquivo);
    atualizaArquivo(nomeArquivo);

    free(nomeArquivo);

    return 0;
}
