/*
Funções para o cabeçalho
Rafael Olivier Cardoso
9436166
*/

#include "register.h"

/*
Inicialmente o cabeçalho terá campos preenchidos com arrobas, para indicar espaço vazio.
Essa função aloca o tamanho necessário dado para um campo do cabeçalho e preenche com arroba.
Parâmetros: Número de bytes a serem alocados
Retorno: String(tam) preenchida com arrobas;
*/
char* preencheArroba(int tam){
    char* str = NULL;
    str = (char*) malloc (tam*sizeof(char));
    int i = 0;

    for(i = 0; i < tam; i++) str[i] = '@';
    str[i-1] = '\0';

    return str;
}

/*
Preenche com char em strings de tamanho 1.
Usado para preencher as tags e o status do cabeçalho.
Parâmetro: Letra a ser preenchida
Retorna uma string(1) com 0 preenchido. (SEM '\0' !!!)
*/
char* preencheLetra(char ch){
    char* str = NULL;
    str = (char*) malloc (1*sizeof(char));
    str[0] = ch;

    return str;
}


/*
Cria um registro do zero, usando as funções para preencher arrobas e zeros
Não há parâmetros.
Retorna um REGISTRO inicializado.
*/
REGISTRO criarRegistro(){

    REGISTRO cabecalho;

    cabecalho.status = NULL;
    cabecalho.tagCampo1 = NULL;
    cabecalho.desCampo1 = NULL;
    cabecalho.tagCampo2 = NULL;
    cabecalho.desCampo2 = NULL;
    cabecalho.tagCampo3 = NULL;
    cabecalho.desCampo3 = NULL;
    cabecalho.tagCampo4 = NULL;
    cabecalho.desCampo4 = NULL;
    cabecalho.tagCampo5 = NULL;
    cabecalho.desCampo5 = NULL;
    cabecalho.preenchePaginaDisco = NULL;

    cabecalho.status = preencheLetra('0');
    cabecalho.topoLista = -1;
    cabecalho.tagCampo1 = preencheLetra('i');
    cabecalho.tagCampo2 = preencheLetra('s');
    cabecalho.tagCampo3 = preencheLetra('t');
    cabecalho.tagCampo4 = preencheLetra('n');
    cabecalho.tagCampo5 = preencheLetra('c');
    cabecalho.desCampo1 = preencheArroba(40);
    cabecalho.desCampo2 = preencheArroba(40);
    cabecalho.desCampo3 = preencheArroba(40);
    cabecalho.desCampo4 = preencheArroba(40);
    cabecalho.desCampo5 = preencheArroba(40);
    cabecalho.preenchePaginaDisco = preencheArroba(31786);

    return cabecalho;
}

REGISTRO zerarRegistro(REGISTRO cabecalho){
    
    int a = 0;

    cabecalho.status[0] = '0';
    cabecalho.topoLista = -1;
    cabecalho.tagCampo1[0] = 'i';
    cabecalho.tagCampo2[0] = 's';
    cabecalho.tagCampo3[0] = 't';
    cabecalho.tagCampo4[0] = 'n';
    cabecalho.tagCampo5[0] = 'c';
    for(a = 0; a < 40; a++) cabecalho.desCampo1[a] = '@';
    cabecalho.desCampo1[a-1] = '\0';
    for(a = 0; a < 40; a++) cabecalho.desCampo2[a] = '@';
    cabecalho.desCampo2[a-1] = '\0';
    for(a = 0; a < 40; a++) cabecalho.desCampo3[a] = '@';
    cabecalho.desCampo3[a-1] = '\0';
    for(a = 0; a < 40; a++) cabecalho.desCampo4[a] = '@';
    cabecalho.desCampo4[a-1] = '\0';
    for(a = 0; a < 40; a++) cabecalho.desCampo5[a] = '@';
    cabecalho.desCampo5[a-1] = '\0';

    return cabecalho;
}