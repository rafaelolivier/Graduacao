#ifndef _MATRIX_FUNCTIONS_H
#define _MATRIX_FUNCTIONS_H

/*
Imprime a matriz, substituindo -1 por .
Parametros: mat (matriz), n (numero de vertices)
Não há retorno
*/
void imprimir_matriz(int** mat, int n);

/*
Imprime vértice adjacente ao vertice entrado
Parametros: mat(matriz), n(numero de vertices)
Não há retorno
*/
void imprimir_vertice (int** mat, int n);

/*
Adiciona uma aresta na matriz
Parâmetros: matriz, dígrafo(É dígrafo = 'D')
Retorno: Matriz novas
*/
int** adicionar_aresta(int** mat, char digrafo);

/*
Aloca os espaços de memória para a matriz e preenche com -1
Parâmetros: n (Numero de vertices)
Retorno: mat (Matriz alocada e preenchida)
*/
int** inicia_matriz(int n);

/*
Preenche a matriz com o peso nas posições onde haverão arestas
Parâmetros: n(numero de vertices), digrafo ('D' é Digrafo, 'G' não é), num_arestas
Retorno: mat(matriz preenchida com os pesos nas posições adequadas)
*/
int** alocar_matriz(int n, char digrafo, int num_arestas);

/*
Remove uma aresta da matriz
Parâmetros: Matriz
Retorno: Matriz
*/
int** remover_aresta(int** mat, char digrafo);

/*
Imprime a matriz transposta
Apenas no caso de digrafo
Parametros: Matriz, quantidade de vertices
Não há retorno
*/
void imprimir_transposto(int** mat, int n);

/*
Imprime aresta com menor peso
Parâmetros: Matriz, numero de vertices
Não há retorno
*/
void imprime_aresta_menor_peso(int** mat, int n);



#endif
