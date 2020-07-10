/*
Cabeçalho para as funções requisitadas no trabalho 1
As três funções aqui inseridas são:

Criar Binário, uma função para transformar um .csv em .bin
Recuperar Dados, uma função que imprime tudo que existe em um .bin
Pesquisar, uma função generica para pesquisar qualquer um dos campos
    retorna uma lista com o byte offset de todos os resultados encontrados.

Rafael Olivier Cardoso
9436166
*/

#ifndef _TRAB1FUNCTIONS_H
#define _TRAB1FUNCTIONS_H

#include "otherfunctions.h"
#include "binfunctions.h"

void criarBin(char* fileName);
void recuperarDados(char* name);
long int* pesquisar(char* fileName, int searchIndex, int remove);

#endif