/*
Cabeçalho para a função de pesquisar
As duas funções aqui inseridas são:
Pesquisar, uma função generica para pesquisar qualquer um dos campos
printCabecalho, que imprime a pesquisa, de acordo com a formatação requisitada.

Rafael Olivier Cardoso
9436166
*/

#ifndef _PESQUISA_H
#define _PESQUISA_H

#include "register.h"

void pesquisar(char* fileName, int searchIndex);
void printCabecalho(REGISTRO reg, int* campoValido);

#endif