/*
Trab 4 - Grafos
Funções relacionadas aos Grafos

Rafael Olivier Cardoso
9436166
*/

#include "matrix_functions.h"

/*
Aloca os espaços de memória para a matriz e preenche com -1
Parâmetros: n (Numero de vertices)
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
			mat[i][j] = FALSE;		//Preenche todas as posições com FALSE (0)
		}
	}

	return mat;
}

/*
Adiciona uma aresta na matriz
Parâmetros: matriz
Retorno: Matriz nova
*/
int** adicionar_aresta(int** mat){

	int v1, v2;
	int peso;

	scanf("%d", &v1);
	scanf("%d", &v2);
	scanf("%d", &peso);

	mat[v1][v2] = peso;    //Atribui o peso a cada aresta
	mat[v2][v1] = peso;

	return mat;
}

/*
Preenche a matriz com 1 nas posições onde haverão arestas
Parâmetros: num_vertices), num_arestas
Retorno: mat(matriz preenchida com os pesos nas posições adequadas)
*/
int** alocar_matriz(int num_vertices, int num_arestas){

	int** mat = NULL;
	int i;

	mat = inicia_matriz(num_vertices);


	for(i=0;i<num_arestas;i++){
		mat = adicionar_aresta(mat);
	}

	return mat;
}

/*
Imprime a matriz, substituindo -1 por .
Parametros: mat (matriz), n (numero de vertices)
Não há retorno
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

void imprimir_vetor(int* vetor, int n){
    int i = 0;
    for(i=0;i<n;i++){
        if(i == n-1){
            printf("%d", vetor[i]);
        }
        else printf("%d ", vetor[i]);
    }
}
