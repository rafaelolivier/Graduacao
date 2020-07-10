/*
Header do Trabalho 3 - Ordenação Topológica

Rafael Olivier Cardoso
9436166
*/

#ifndef _ORDEM_TOPOLOGICA_H_
#define _ORDEM_TOPOLOGICA_H_

#define BRANCO 0
#define CINZA 1
#define PRETO 2

void checar_vertice(int** matriz, int n_vert, int i, int* vetorCor, int* tempo, int* p, int* tempo1, int* tempo2);
int* iniciar_vetor_cor(int n_vert);
int* iniciar_vetor_tempo(int n_vert);
int* ordenacao_topologica(int** matriz, int n_vert);
int encontrar_maior(int n_vert, int* tempo);
int* ordenar_vetor(int n_vert, int* tempo2);


#endif
