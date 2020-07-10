/*
Cabeçalho do Registro

Rafael Olivier Cardoso 9436166
Leandro Sena Silva 9293060
*/

#ifndef _CABECALHO_H
#define _CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct head HEAD;

struct head{
    char status;
    int RRNproxRegistro;
    int numeroRegistrosInseridos;
    int numeroRegistrosRemovidos;
    int numeroRegistrosAtualizados;
    char* lixo;
};

void escreverHead(FILE* bin, HEAD head);
HEAD criarHead();
HEAD obterHead(FILE* bin, HEAD head);
void imprimirHead(HEAD head);

#endif