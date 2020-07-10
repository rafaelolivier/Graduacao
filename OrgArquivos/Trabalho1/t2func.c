/*
Cabeçalho para as funções da segunda parte do trabalho (Trabalho 2)
As funções são para remover, inserir e atualizar registros binários em um arquivo já existente.
Diferentemente das funções do trabalho 1, as novas funcionalidades estarão localizadas em um único .c
pela organização e para facilitar a correção das novas funções.

Rafael Olivier Cardoso
9436166
*/

#ifndef _T2FUNC_H
#define _T2FUNC_H

#include "register.h"

void removerRegistro(char* fileName);
void inserirRegistro(char* fileName);
void atualizarRegistro(char* fileName);

#endif