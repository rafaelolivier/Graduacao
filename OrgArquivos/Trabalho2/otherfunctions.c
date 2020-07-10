/*
Funções auxiliares para execução das funções.

Rafael Olivier Cardoso
9436166
*/

#include "otherfunctions.h"

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

/*
Função para impressão de um cabeçalho, com indicador de quais campos imprimir.
Parâmetros: Registro cabeçalho, vetor de inteiros (booleanos) com a validade de cada campo.
Não há retorno.
*/
void printCabecalho(REGISTRO reg, int* campoValido){
    printf("numero de identificacao do servidor: ");
    printf("%s\n", reg.desCampo1);

    printf("salario do servidor: ");
    if(campoValido[1] == 1) printf("%s\n", reg.desCampo2);
    else printf("valor nao declarado\n");

    printf("telefone celular do servidor: ");
    if(campoValido[2] == 1) printf("%s\n", reg.desCampo3);
    else printf("valor nao declarado\n");

    printf("nome do servidor: ");
    if(campoValido[3] == 1) printf("%s\n", reg.desCampo4);
    else printf("valor nao declarado\n");

    printf("cargo do servidor: ");
    if(campoValido[4] == 1 && reg.desCampo5[1] != '@') printf("%s\n", reg.desCampo5);
    else printf("valor nao declarado\n");

    printf("\n");
}

/*
Função para pegar uma string na entrada padrão.
Aloca 40 bytes de memória, pois nenhum nome passa desse tamanho.
Não há parâmetros.
Retorna uma string com \0 no final.
*/
char* getName(){

    char* name = NULL;
    char aux;

    name = (char*)malloc(40*sizeof(char));
    int i = 0;
    aux = getchar();
    while(aux != ' ' && aux != '\n' && aux != EOF){
        name[i] = aux;
        i++;
        aux = getchar();
    }
    name[i] = '\0';

    return name;
}

/*
Função organizar a pesquisa no arquivo binário.
Passa para a função principal os parâmetros inseridos pelo usuário
Não há Parâmetros
Retorna o código de operação
*/
int definirCampo(){
    //A operação depende do tipo de dado que o usuário deseja pesquisar
    char* nomeDoCampo;
    nomeDoCampo = getName();

    //Os campos podem ser: 
    //  "idServidor", "salarioServidor", "telefoneServidor", "nomeServidor" e "cargoServidor"
    //Como todos eles tem letras iniciais diferentes, será usada uma operação de Switch com char
    char op = nomeDoCampo[0];
    switch (op){
        case 'i':
            free(nomeDoCampo);
            return 0;
        
        case 's':
            free(nomeDoCampo);
            return 1;
        
        case 't':
            free(nomeDoCampo);
            return 2;
        
        case 'n':
            free(nomeDoCampo);
            return 3;
        
        case 'c':
            free(nomeDoCampo);
            return 4;
    }
}


char* getDesCampo(FILE* fp, char* campo){
    int i = 0;
    char aux;

    aux = getc(fp);
    while(aux != '\n' && aux != '\0' && aux != ','){
        campo[i] = aux;
        aux = getc(fp);
        i++;
    }
    i=0;

    return campo;
}


REGISTRO getCabecalhoCSV(FILE* fp, REGISTRO cabecalho){
    
    cabecalho.desCampo1 = getDesCampo(fp, cabecalho.desCampo1);
    cabecalho.desCampo2 = getDesCampo(fp, cabecalho.desCampo2);
    cabecalho.desCampo3 = getDesCampo(fp, cabecalho.desCampo3);
    cabecalho.desCampo4 = getDesCampo(fp, cabecalho.desCampo4);
    cabecalho.desCampo5 = getDesCampo(fp, cabecalho.desCampo5);

    return cabecalho;
}