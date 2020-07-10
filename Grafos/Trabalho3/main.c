/*
Lab 3 - Grafos
Ordenação Topológica

Rafael Olivier Cardoso
9436166
*/

#include "matrix_functions.h"
#include "ordem_topologica.h"

int main (void){

    int num_vertices = -1;
	int num_arestas = -1;

    scanf("%d", &num_vertices);
	scanf("%d", &num_arestas);

	int** matriz = NULL;
	matriz = alocar_matriz(num_vertices, num_arestas);

    int* vetor_ordenado = ordenacao_topologica(matriz, num_vertices);
    imprimir_vetor(vetor_ordenado, num_vertices);

	int i = 0;
	for(i=0;i<num_vertices;i++){
        free(matriz[i]);
    }
    free(matriz);
    free(vetor_ordenado);

    return 0;
}
