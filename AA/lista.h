/*
Header das funções usadas para resolver o problema do sequenciamento
Inclue a lista necessária
*/

#ifndef LISTA_H
#define LISTA_H

#define TRUE 0
#define FALSE 1
#define boolean int

#include <stdio.h>
#include <stdlib.h>

typedef struct BLOCO{

    int id;
    int deadline;
    int profit;
    struct BLOCO *prox;
}NO;

typedef struct{

    NO* inicio;
    NO* fim;
}Lista;


void cria_Lista(Lista *L);
void inserir_Lista(Lista *L, NO* no, NO* anterior, int qtdTarefas, int i);
void imprime_Lista(Lista *L);
boolean libera_Lista(Lista *L);
int maxDeadLine(Lista *L);

#endif