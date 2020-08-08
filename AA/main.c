/*
Sequenciamento de Tarefas

Programa que tenta encontrar o maior lucro para uma lista de tarefas com prazo máximo.
*/
#include "lista.h"

int calculaLucro(Lista *L, int MDL){
    
    NO *aux = L->inicio;
    NO *anterior = L->inicio;
    NO *curr = (NO*) malloc (sizeof(NO));;
    curr->profit = 0;

    int *vet = NULL;
    vet = (int*) malloc (MDL*sizeof(int));
    
    int soma = 0;
    int i, j, count = 0, flag;
    for(i = 0; i < MDL; i++) vet[i] = 0;

    for(i = MDL; i > 0; i--){

        aux = L->inicio;
        while(aux != NULL){
            if(aux->deadline >= i && aux->profit > curr->profit){
                flag = 0;
                for(j = 0; j < count; j++){
                    if(vet[j] == aux->id) flag = 1;
                }
                if(flag == 0){
                    curr->profit = aux->profit;
                    curr->deadline = aux->deadline;
                    curr->id = aux->id;
                    vet[count] = aux->id;
                }
            }
            aux = aux->prox;
        }
        count++;
        soma = soma + curr->profit;
        printf("ID: %d DeadLine: %d Profit: %d\n", curr->id, curr->deadline, curr->profit);
        curr->profit = 0;
    }

    free(curr);
    free(vet);

    return soma;
}

int main(int argc, char* argv[]){

    Lista L;
    cria_Lista(&L);

    int qtdTarefas;
    scanf("%d", &qtdTarefas);
    inserir_Lista(&L, NULL, NULL, qtdTarefas, 1);

    int MDL = maxDeadLine(&L);
    int soma = calculaLucro(&L, MDL);
    printf("Lucro Máximo: %d\n", soma);

    libera_Lista(&L);

    return 0;
}