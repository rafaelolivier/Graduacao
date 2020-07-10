/*
Funções de preenchimento do cabecalho

Rafael Olivier Cardoso 9436166
Leandro Sena Silva 9293060
*/

#include "cabecalho.h"

/*
Sobreescreve todo o cabecalho, o conteúdo deve ser dado nos parâmetros.
Parâmetros: Arquivo onde será escrito (já aberto), cabeçalho a ser escrito.
Não há retorno, mas o ponteiro do arquivo voltará ao inicio.
*/
void escreverHead(FILE* bin, HEAD head){
    rewind(bin);
    fwrite(&head.status, sizeof(char), 1, bin);
    fwrite(&head.RRNproxRegistro, sizeof(int), 1, bin);
    fwrite(&head.numeroRegistrosInseridos, sizeof(int), 1, bin);
    fwrite(&head.numeroRegistrosRemovidos, sizeof(int), 1, bin);
    fwrite(&head.numeroRegistrosAtualizados, sizeof(int), 1, bin);
    fwrite(head.lixo, sizeof(char), 111, bin);
}

/*
Aloca o cabecalho inicializado
Parâmetros: não há
Retorno: Cabeçalho inicializado.
*/
HEAD criarHead(){
    HEAD head;
    head.status = '0';
    head.RRNproxRegistro = 0;
    head.numeroRegistrosInseridos = 0;
    head.numeroRegistrosRemovidos = 0;
    head.numeroRegistrosAtualizados = 0;
    
    int a = 0;
    head.lixo = (char*)malloc(111*sizeof(char));
    for(a = 0; a<111; a++) head.lixo[a] = '$';

    return head;
}

/*
Obtém head de dentro de um arquivo.
Parâmetros: arquivo binario, cabeçalho a ser alocado
Retorno: Cabeçalho a ser alocado
*/
HEAD obterHead(FILE* bin, HEAD head){
    rewind(bin);
    fread(&head.status, sizeof(char), 1, bin);
    fread(&head.RRNproxRegistro, sizeof(int), 1, bin);
    fread(&head.numeroRegistrosInseridos, sizeof(int), 1, bin);
    fread(&head.numeroRegistrosRemovidos, sizeof(int), 1, bin);
    fread(&head.numeroRegistrosAtualizados, sizeof(int), 1, bin);
    fread(head.lixo, sizeof(char), 111, bin);

    return head;
}

//Imprime head, função de debugg
void imprimirHead(HEAD head){
    printf("status: %c\n", head.status);
    printf("RRN: %d\n", head.RRNproxRegistro);
    printf("INS: %d\n", head.numeroRegistrosInseridos);
    printf("REM: %d\n", head.numeroRegistrosRemovidos);
    printf("ATT: %d\n", head.numeroRegistrosAtualizados);
}