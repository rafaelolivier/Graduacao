/*
Header do Trabalho 3 - Funções dos Grafos

Rafael Olivier Cardoso
9436166
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _MATRIX_FUNCTIONS_H_
#define _MATRIX_FUNCTIONS_H_

#define FALSE -1
#define TRUE 0

int** alocar_matriz(int num_vertices, int num_arestas);
int** inicia_matriz(int n);
int** adicionar_aresta(int** mat);
void imprimir_matriz(int** mat, int n);
void imprimir_vetor(int* vetor, int n);

#endif

