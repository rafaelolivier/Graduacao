/*
Cabeçalho do Registro

Rafael Olivier Cardoso
9436166
*/

#ifndef _REGISTER_H
#define _REGISTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct registro REGISTRO;

struct registro{
    char* status;       //0 para aberto, 1 para fechado
    long int topoLista; //8 bytes para byte offset
    char* tagCampo1;    //resumo de idServidor
    char* desCampo1;    //descrição de idServidor
    char* tagCampo2;    //resumo de salário do servidor
    char* desCampo2;    //descrição de salário do servidor
    char* tagCampo3;    //resumo de telefone do servidor
    char* desCampo3;    //descrição de telefone do servidor
    char* tagCampo4;    //resumo de nome do servidor
    char* desCampo4;    //descrição de nome do servidor
    char* tagCampo5;    //resumo de cargo do servidor
    char* desCampo5;    //descrição de cargo do servidor
    //Ocupado 214 bytes
    char* preenchePaginaDisco;
};

char* preencheLetra(char ch);
char* preencheArroba(int tam);
REGISTRO criarRegistro();
REGISTRO zerarRegistro(REGISTRO cabecalho);

#endif