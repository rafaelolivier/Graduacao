/*
Lab 4 - Grafos
MST - PRIM

Rafael Olivier Cardoso
9436166
*/

#include "matrix_functions.h"
#include "mst.h"

int main (void){

    int num_vertices = -1;
	int num_arestas = -1;

    scanf("%d", &num_vertices);
	scanf("%d", &num_arestas);

	int** matriz = NULL;
	matriz = alocar_matriz(num_vertices, num_arestas);

    prim(matriz, num_vertices);

	int i = 0;
	for(i=0;i<num_vertices;i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

