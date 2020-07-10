/*
Header para funções para manipulação de arquivos binários, como read e write

Rafael Olivier Cardoso
9436166
*/

#ifndef _BINFUNCTIONS_H
#define _BINFUNCTIONS_H

#include "otherfunctions.h"

typedef struct data DATA;

struct data{

    //Dados inseridos ou retirados do binário
    char removido;    //Indica se é um elemento removido
    long int encadeamentoLista;    //Indica o proximo elemento removido da lista
    int tamRegistro; //grava o tamanho do registro
    int idServidor;     //Grava o id do servidor
    double salarioServidor;   //grava o salário do servidor
    char* telefoneServidor;  //grava o telefone do servidor - tem sempre 14 bytes
    int tamString1; //grava o tamanho do nome
    char delimCampo4; //grava o delimitador 'n' do nome
    char* nomeServidor;  //grava o nome do servidor
    int tamString2; //grava o tamanho do cargo
    char delimCampo5;  //Grava os delimitador 'c' do cargo
    char* cargoServidor; //grava o cargo do servidor
};

DATA createBlock();
int binWriteBlock(DATA block, FILE* bin, int dv1, int dv2, long int byteCounter, int tamAnterior);
DATA binReadBlock(FILE* bin, DATA block, long int* byteCounter);
void escreverCabecalho(FILE* bin, REGISTRO cabecalho);
REGISTRO lerCabecalho(FILE* bin, REGISTRO cabecalho);

#endif