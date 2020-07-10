/*
Header do Trabalho 4 - MST - PRIM

Rafael Olivier Cardoso
9436166
*/

#ifndef _MST_H_
#define _MST_H_

#define INFI 9999999

typedef struct tupla TUPLA;

TUPLA* atualizar_custo(TUPLA* t, int vertice, int custo);
int extrair_minimo(TUPLA* t, int n);
void prim(int** grafo, int num_vertices);

#endif
