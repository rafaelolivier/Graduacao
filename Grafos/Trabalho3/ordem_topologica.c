/*
Arquivo com a fun��es que realizam a Ordena��o Topol�gica
Rafael Olivier Cardoso
9436166
*/

#include "ordem_topologica.h"
#include "matrix_functions.h"


/*
Inicia o vetor que conter� as cores

    Para a ordena��o topol�gica, usa-se cores para indicar o estado da aresta
    0 - Branco - Ainda n�o acessado
    1 - Cinza - Acessado mas n�o finalizado
    2 - Preto - Finalizado

Par�metros: N�mero de vertices no grafo
Retorno: Vetor de cores
*/
int* iniciar_vetor_cor(int n_vert){

    int* cor = (int*)malloc(n_vert*sizeof(int));
	int i;
	for (i=0; i<n_vert; i++){
		cor[i] = BRANCO;
	}
	return cor;
}

/*
Inicializa o vetor tempo
Par�metros: N�mero de v�rtices
Retorno: Vetor tempo
*/
int* iniciar_vetor_tempo(int n_vert) {

	int* tempo = (int*)malloc(n_vert*sizeof(int));
	int i = 0;
	//Preenche as posi��es do vetor com 0
	for (i=0; i<n_vert; i++){
		tempo[i] = 0;
	}
	return tempo;
}

void checar_vertice(int** matriz, int n_vert, int i, int* vetorCor, int* tempo, int* p, int* tempo1, int* tempo2){

	vetorCor[i] = CINZA;
	(*tempo)++;
    tempo1[i] = (*tempo);

	int j;
	for (j=0; j<n_vert; j++) {
		if (vetorCor[j] == BRANCO && matriz[i][j] == 0) {
            p[j] = i;   //p recebe o valor antigo na posi��o a sendo acessada
            checar_vertice(matriz, n_vert, j, vetorCor, tempo, p, tempo1, tempo2);
		}
	}

	vetorCor[i] = PRETO;
	(*tempo)++;
	tempo2[i] = (*tempo);
}

/*
Encontra o maior inteiro dentro de um vetor de inteiros
Eficiencia O(n)
Par�metros: Tamanho do vetor, vetor de inteiros
Retorno: Maior inteiro
*/
int encontrar_maior(int n_vert, int* tempo){
    int aux = -1;
    int i = 0;
    for(i=0; i<n_vert;i++){
        if(aux < tempo[i]){
            aux = tempo[i];
        }
    }
    return aux;
}
/*
Agora os vetores est�o preenchidos � necess�rio orden�-lo
A cada impress�o, chama a fun��o para encontrar o pr�ximo vertice a ser impresso. Para isso precisaremos percorrer o vetor tempo2, encontrando o maior em cada passagem e imprimindo.
Par�metros: Numero de vertices, vetor com os valores de peso
Retorno: Vetor ordenado
*/
int* ordenar_vetor(int n_vert, int* tempo2){

    int* vetor_resposta = iniciar_vetor_tempo(n_vert);
    int j, i, maior = -1;
    maior = encontrar_maior(n_vert, tempo2);
    for (i=0; i<n_vert; i++){       //Essa passagem garante que rode n� vezes, fazendo com que todos os v�rtices sejam pegos
        for(j=0; j<n_vert; j++){    //Essa encontra o maior v�rtice no vetor
            if(tempo2[j] == maior){
                vetor_resposta[i] = j;
                tempo2[j] = -1;
                maior = encontrar_maior(n_vert, tempo2);
                break;      //Para impedir repeti��es
            }
        }
    }

    return vetor_resposta;
}

/*
Fun��o que guiar� a ordena��o topol�gica
Par�metros: Matriz (int**) e N�mero de v�rtices (int)
N�o h� retorno
*/
int* ordenacao_topologica(int** matriz, int n_vert){

    int* vetorCor = iniciar_vetor_cor(n_vert);
    int* p = iniciar_vetor_tempo(n_vert);
    int* tempo1 = iniciar_vetor_tempo(n_vert);
    int* tempo2 = iniciar_vetor_tempo(n_vert);

    int i, tempo = 0;
    for(i = 0;i<n_vert;i++){
        if(vetorCor[i] == BRANCO){
            checar_vertice(matriz, n_vert, i, vetorCor, &tempo, p, tempo1, tempo2);
        }
    }

    int* vetor_resposta = ordenar_vetor(n_vert, tempo2);

    //Libera a mem�ria alocada nessa fun��o
    free(vetorCor);
    free(p);
    free(tempo1);
    free(tempo2);

    return vetor_resposta;
}

