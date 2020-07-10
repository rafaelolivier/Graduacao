/*
Cabeçalho para as funções da segunda parte do trabalho (Trabalho 2)
As funções são para remover, inserir e atualizar registros binários em um arquivo já existente.

Rafael Olivier Cardoso
9436166
*/

#ifndef _TRAB2FUNCTIONS_H
#define _TRAB2FUNCTIONS_H

#include "otherfunctions.h"
#include "binfunctions.h"
#include "trab1functions.h"

void removerRegistro(char* fileName);
void inserirRegistro(char* fileName);
void atualizarRegistro(char* fileName);

#endif