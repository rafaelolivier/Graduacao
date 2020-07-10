/*
Trab 4 - Grafos
Funções para gerar uma MST com algoritmo PRIM

Rafael Olivier Cardoso
9436166
*/

#include "mst.h"
#include "matrix_functions.h"


//A posição que ela se encontra na lista indicará o vértice adjacente
struct tupla{

    int vertice;
    int custo;

};

TUPLA* atualizar_custo(TUPLA* t, int vertice, int custo){

	t[vertice].custo = custo;
	return t;
}

int extrair_minimo(TUPLA* t, int n){

	int i = 0;

	TUPLA aux;
	aux.custo = INFI;
	aux.vertice = -1;

	for(i=0; i < n; i++){
		if(t[i].custo < aux.custo){
			aux.vertice = t[i].vertice;
		}
	}	

	return aux.vertice;
}

/*
Organiza quais funções chamar, ao fim terá executado o algoritmo Prim para grafos em matrizes e imprimido na tela
Parâmetros: Grafo e número de vértices nele
Não há retorno.
*/
void prim(int** grafo, int num_vertices){
	int i = 0;

	int* vetor_predecessor = NULL;
	vetor_predecessor = (int*) malloc (num_vertices*sizeof(int));
	for(i = 0; i < num_vertices; i++){
		vetor_predecessor[i] = -1;
	}

	TUPLA* t = NULL;
	t = (TUPLA*) malloc (num_vertices*sizeof(TUPLA));

	for(i=0; i < num_vertices; i++){
		vetor_predecessor[i] = -1;
		t[i].vertice = i;
		t[i].custo = INFI;
	}
	//Coloca custo 0 no vértice 0 (inicial)
	t = atualizar_custo(t, 0, 0);

	int* vetor_vertices = NULL;
	vetor_vertices = (int*) malloc (num_vertices*sizeof(int));

	//enquanto nao faltar nenhum vertice para incluir
	int ninclusos, u;

	for (ninclusos = num_vertices-1; ninclusos > 0; ninclusos--){
		u = extrair_minimo(t, num_vertices);
		vetor_vertices[u] = 1;	//Marca como visitado
		
		//Percorrer todos os adjacentes
		for(i = 0; i < num_vertices; i++){
			//Se for adjacente, ou seja, se tem uma aresta com peso maior que zero entre as duas...
			if (grafo[u][i] > 0){
				//se ainda nao foi colocado na arvore e o valor da aresta é menor que o marcado em "peso"
				printf("chegou aqui\n");
                		if (!vetor_vertices[i] && grafo[u][i] < t[i].custo){
					printf("Aqui não\n");    
					t[i].custo = grafo[u][i];                			
					vetor_predecessor[i] = u;
                		}
			}
		}
	}
	imprimir_vetor(vetor_predecessor, num_vertices);
}
