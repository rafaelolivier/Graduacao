/*
Funções envolvendo a lista do sequenciamento de atividades
*/

#include "lista.h"

void cria_Lista(Lista *L){
    L->inicio = NULL;
    L->fim = NULL;
}

boolean libera_Lista(Lista *L){
    if(L->inicio == NULL) return TRUE;
    NO *aux = L->inicio;
    while(aux != NULL){
        L->inicio = L->inicio->prox;
        free(aux);
        aux = L->inicio;
    }
}

void inserir_Lista(Lista *L, NO* atual, NO* anterior, int qtdTarefas, int i){

    NO *novo = (NO*) malloc (sizeof(NO));
    if(novo == NULL) exit(1);

    novo->id = i;
    scanf("%d", &novo->deadline);
    scanf("%d", &novo->profit);
    novo->prox = NULL;
    atual = novo;

    if(i != 1) anterior->prox = atual;

    if(i < qtdTarefas) inserir_Lista(L, atual->prox, atual, qtdTarefas, i+1);
    else L->fim = atual;

    if(i == 1) L->inicio = atual;
}

int maxDeadLine(Lista *L){
    NO *aux = L->inicio;
    int max = 0;
    while(aux != NULL){
        if(aux->deadline > max) max = aux->deadline;
        aux = aux->prox; 
    }
    return max;
}

void imprime_Lista(Lista *L){
    NO *aux = L->inicio;
    while(aux != NULL){
        printf("ID: %d   DeadLine: %d   Profit: %d\n", aux->id, aux->deadline, aux->profit);
        aux = aux->prox;
    }
}