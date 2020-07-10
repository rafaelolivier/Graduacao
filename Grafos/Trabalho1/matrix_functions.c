
#include <stdio.h>
#include <stdlib.h>
#include "matrix_functions.h"

/*
Imprime a matriz, substituindo -1 por .
Parametros: mat (matriz), n (numero de vertices)
N�o h� retorno
*/
void imprimir_matriz(int** mat, int n){

	int i = 0, j =0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
            if(j != n-1){
                if(mat[i][j] == -1) printf(". ");
                else{
                    printf("%d ", mat[i][j]);
                }
            }else{
                if(mat[i][j] == -1) printf(".\n");
                else{
                    printf("%d\n", mat[i][j]);
                }
            }
		}
	}

}

/*
Imprime v�rtice adjacente ao vertice entrado
Parametros: mat(matriz), n(numero de vertices)
N�o h� retorno
*/
void imprimir_vertice (int** mat, int n){

	int x = 0;
	int* aux = NULL;
	int i, j=0, count = 0;
	int bs;

	scanf("%d", &x);
	aux = (int*) malloc (n*sizeof(int));	//o vetor ter� no m�ximo n posi��es preenchidas


	//Preencher o vetor auxiliar com os numeros a serem impressos
	for(i=0; i<n; i++){
		if(mat[x][i] != -1){
			aux[j] = i;
			j++;
			count++;
		}
	}

	//ordenar os n�meros, como n�o s�o muitos, usa um simples bubblesort
	for(i=1;i<count;i++){
		for(j=0;j<count-1;j++){
			if(aux[j] > aux[j+1]){
				bs = aux[j];
               			aux[j] = aux[j + 1];
                		aux[j + 1] = bs;
			}
		}
	}

	//Agora com os numeros ordenados, imprime
	for(i=0;i<count;i++){
        if(i != count-1){
            printf("%d ", aux[i]);
        }
        else{
            printf("%d\n", aux[i]);
        }
	}

}

/*
Adiciona uma aresta na matriz
Par�metros: matriz, d�grafo(� d�grafo == 'D')
Retorno: Matriz novas
*/
int** adicionar_aresta(int** mat, char digrafo){

	int v1, v2, peso;
	scanf("%d", &v1);
	scanf("%d", &v2);
	scanf("%d", &peso);

	mat[v1][v2] = peso;
	if(digrafo == 'G') mat[v2][v1] = peso;		//Se n�o for digrafo, a arestas funcionam para ambas as dire��es, portanto devemos preencher o inverso tamb�m.

	return mat;
}

/*
Aloca os espa�os de mem�ria para a matriz e preenche com -1
Par�metros: n (Numero de vertices)
Retorno: mat (Matriz alocada e preenchida)
*/
int** inicia_matriz(int n){

	int** mat = NULL;
	mat = (int**) malloc (n*sizeof(int*));
	int i = 0, j =0;
	for(i=0;i<n;i++){
		mat[i] = (int*) malloc (n*sizeof(int*));
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			mat[i][j] = -1;		//Preenche todas as posi��es com -1 ao inv�s de pontos. Para regularizar para o run codes, os -1's ser�o transformados em . na impress�o.
		}
	}

	return mat;
}

/*
Preenche a matriz com o peso nas posi��es onde haver�o arestas
Par�metros: n(numero de vertices), digrafo ('D' � Digrafo, 'G' n�o �), num_arestas
Retorno: mat(matriz preenchida com os pesos nas posi��es adequadas)
*/
int** alocar_matriz(int n, char digrafo, int num_arestas){

	int** mat = NULL;
	int i;

	mat = inicia_matriz(n);


	for(i=0;i<num_arestas;i++){
		mat = adicionar_aresta(mat, digrafo);
	}

	return mat;
}


/*
Remove uma aresta da matriz
Par�metros: Matriz e Char Digrafo
Retorno: Matriz
*/
int** remover_aresta(int** mat, char digrafo){

	int v1, v2;
	scanf("%d", &v1);
	scanf("%d", &v2);

	mat[v1][v2] = -1;

	//Se n�o for digrafo, deve apagar ambos as dire��es 
	if(digrafo == 'G') mat[v2][v1] = -1;

	return mat;
}

/*
Imprime a matriz transposta
Apenas no caso de digrafo
Parametros: Matriz, quantidade de vertices
N�o h� retorno
*/
void imprimir_transposto(int** mat, int n){

	int i = 0, j =0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
            if(j != n-1){
                if(mat[j][i] == -1) printf(". ");
                else{
                    printf("%d ", mat[j][i]);
                }
            }
            else{
                if(mat[j][i] == -1) printf(".\n");
                else{
                    printf("%d\n", mat[j][i]);
                }
            }
		}
	}

}
/*
Imprime aresta com menor peso
Par�metros: Matriz, numero de vertices
N�o h� retorno
*/
void imprime_aresta_menor_peso(int** mat, int n){

	int i, j, aux = 50000, auxx =-1, auxy = -1;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(mat[i][j] != -1){
				if(aux > mat[i][j]){
					aux = mat[i][j];
					auxx = i;
					auxy = j;
				}
			}
		}
	}

	if (auxx <= auxy) printf("%d %d\n", auxx, auxy);
	if (auxx > auxy) printf("%d %d\n", auxy, auxy);

}
