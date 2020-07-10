/*
Lab 1 - Grafos
Contruir um TAD para Grafos com Matriz

Rafael Olivier Cardoso
9436166
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix_functions.h"

/*
Recebe a instrução na entrada padrão. Pede letras até encontrar um espaço.
Parâmetros: Nenhum
Retorno: Instrução (string)
*/
char* get_intruction(void){

	char* instruct;
	char aux = 0;
	int i = 0;
	instruct = (char*)malloc(10*sizeof(char));	//10 bytes devem ser o suficiente para qualquer instrução

	aux = getchar();
	while(aux != ' ' && aux != '\n' && aux != EOF){
		instruct[i] = aux;
		i++;
		aux = getchar();
		if(aux == EOF) instruct[9] = 'E';
	}



	return instruct;
}

int main(void){

	char digrafo;				//D = Digrafo   G = Não Dígrafo
	char TAD;					//M = Matriz	L = Lista
	int num_vertices = -1;
	int num_arestas = -1;
	int i = 0;


	//Primeira linha de entrada
	digrafo = getchar();
	getchar();
	TAD = getchar();
	getchar();

	scanf("%d", &num_vertices);
	scanf("%d", &num_arestas);
	//Fim da primeira linha de entrada

	if(TAD == 'M'){
		int** matriz = NULL;

		matriz = alocar_matriz(num_vertices, digrafo, num_arestas);

        char* instruct;

        instruct = get_intruction();
        while(instruct[0] != 'E' && instruct[9] != 'E'){					//Não incluso no run.codes, mas fica como condição de parada adicional além de fechar o programa

            if(instruct[0] == 'E') exit(1);
            if(instruct[0] == 'I' && instruct[1] == 'G') imprimir_matriz(matriz, num_vertices);
            if(instruct[0] == 'V') imprimir_vertice(matriz, num_vertices);
            if(instruct[0] == 'A') matriz = adicionar_aresta(matriz, digrafo);
            if(instruct[0] == 'R') matriz = remover_aresta(matriz, digrafo);
            if(instruct[0] == 'I' && instruct[1] == 'T'){
                if(digrafo == 'D') imprimir_transposto(matriz, num_vertices);
            }
            if(instruct[0] == 'M') imprime_aresta_menor_peso(matriz, num_vertices);

            free(instruct);			//Libera as informações antigas, agora inválidas
            instruct = get_intruction();	//Pega novas instruções
        }
                //Liberando espaço alocado
        for(i=0;i<num_vertices;i++){
            free(matriz[i]);
        }
        free(matriz);
        free(instruct);

	}


	return 0;
}
