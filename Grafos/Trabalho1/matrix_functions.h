#ifndef _MATRIX_FUNCTIONS_H
#define _MATRIX_FUNCTIONS_H

/*
Imprime a matriz, substituindo -1 por .
Parametros: mat (matriz), n (numero de vertices)
N�o h� retorno
*/
void imprimir_matriz(int** mat, int n);

/*
Imprime v�rtice adjacente ao vertice entrado
Parametros: mat(matriz), n(numero de vertices)
N�o h� retorno
*/
void imprimir_vertice (int** mat, int n);

/*
Adiciona uma aresta na matriz
Par�metros: matriz, d�grafo(� d�grafo = 'D')
Retorno: Matriz novas
*/
int** adicionar_aresta(int** mat, char digrafo);

/*
Aloca os espa�os de mem�ria para a matriz e preenche com -1
Par�metros: n (Numero de vertices)
Retorno: mat (Matriz alocada e preenchida)
*/
int** inicia_matriz(int n);

/*
Preenche a matriz com o peso nas posi��es onde haver�o arestas
Par�metros: n(numero de vertices), digrafo ('D' � Digrafo, 'G' n�o �), num_arestas
Retorno: mat(matriz preenchida com os pesos nas posi��es adequadas)
*/
int** alocar_matriz(int n, char digrafo, int num_arestas);

/*
Remove uma aresta da matriz
Par�metros: Matriz
Retorno: Matriz
*/
int** remover_aresta(int** mat, char digrafo);

/*
Imprime a matriz transposta
Apenas no caso de digrafo
Parametros: Matriz, quantidade de vertices
N�o h� retorno
*/
void imprimir_transposto(int** mat, int n);

/*
Imprime aresta com menor peso
Par�metros: Matriz, numero de vertices
N�o h� retorno
*/
void imprime_aresta_menor_peso(int** mat, int n);



#endif
