/*
T5 - Gerenciador de Abas na Internet
Rafael Olivier Cardoso
9436166
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct node NODE;
typedef struct lista LISTA;

struct node{
    NODE* prox;
    char* titulo;
    char* URL;
    int mes;
    int dia;
    int hora;
    int minuto;
};

struct lista{
    NODE* raiz;
    int tam;
};


/*
Pega uma string até achar \n e o substitui por \0 no final.
Não há parâmetros, mas exige entrada de dados via stdin.
Retorna string.
*/
char* getString(){

    char aux = 1;
    char* str = NULL;
    int tam = 0;

    while(aux != '\n'){
        aux = getchar();
        tam++;
        str = (char*) realloc (str, tam*sizeof(char));
        str[tam-1] = aux;
    }
    str[tam-1] = '\0';

    return str;
}
/*
    Percorre a lista recursivamente até chegar na posição desejada.
    Adiciona um nó na lista dado como parâmetros e pode setar o próximo elemento como nulo caso seja a ultima posição.
    Parâmetros: Nó sendo alterado, lista a ser percorrida, nó a ser copiado, pos a ser adicionado, posição inicial/atual.
    Retorno: Não há, mas a lista modifica internamente com novo elemento posicionado.
*/
void percorrerLista(NODE** no, LISTA* lista, NODE* aux, int posfinal, int currpos){

    if(currpos < posfinal) percorrerLista(&(*no)->prox, lista, aux, posfinal, currpos+1);
    else{
        (*no) = (NODE*) malloc (1*sizeof(NODE));
        (*no) = aux;
        if(currpos == lista->tam) (*no)->prox = NULL;
    }
}

/*
Libera todas as posições da lista
Parâmetros: Lista e endereço da raiz da lista
Retorno: Não há, mas a lista modifica internamente.
*/
void liberarLista(NODE* no, LISTA* lista){

    if(no->prox != NULL) liberarLista(no->prox, lista);
    free(no->titulo);
    free(no->URL);
    free(no);
}

/*
    Caso o nó raiz esteja vazio, inicia a lista
    Caso não, chama a função para percorrer a lista e adicionar a nova entrada
    Parâmetros: Lista a ser verificada, nó a ser adicionado
    Retorno: Não há, mas a lista modifica internamente.
*/
void adicionarAba(LISTA* lista, NODE* aux){

    if(lista->raiz == NULL){
        lista->raiz = (NODE*) malloc (1*sizeof(NODE));
        lista->raiz = aux;
        lista->raiz->prox = NULL;
    }
    else{
        percorrerLista(&lista->raiz->prox, lista, aux, lista->tam, 1);
    }
}

/*
    Insere pela primeira vez uma aba. Pega entradas do teclado
    Parâmetros: Lista
    Retorno: Não há, mas a lista modifica internamente.
*/
void inserir(LISTA* lista){

    NODE* aux = (NODE*) malloc (1*sizeof(NODE));
    aux->titulo = getString();
    aux->URL = getString();
    scanf("%d", &aux->dia);
    scanf("%d", &aux->mes);
    scanf("%d", &aux->hora);
    scanf("%d", &aux->minuto);
    adicionarAba(lista, aux);
    free(aux);
}

/*
Retorna a posição inicial para a troca, a posição inicial é o primeiro item na lista que tem um título igual ao fornecido.
Caso não haja um titulo igual ao dado na lista, retorna -1;
Parâmetros: Lista, nó raiz, título a ser comparado, pos (inicial = 1);
Retorno: Posição inicial do elemento da lista a ser trocado.
*/
int determinarPosInicial(LISTA* lista, NODE* no, char* titulo, int pos){

    if(pos > lista->tam) return -1;
    if(strcmp(no->titulo, titulo) == 0) return pos;
    pos = determinarPosInicial(lista, no->prox, titulo, pos+1);
}

/*
Troca a posição de uma aba. Caso a nova posição seja maior que o tamanho da lista, posiciona no final.
Parâmetros: Lista a ser alterada, posição inicial da aba a ser trocada, posição de destino da troca
Retorno: Não há, mas a lista modifica internamente com uma das abas em nova posição
*/
void trocarAba(LISTA* lista, int posinicial, int posfinal){

    //Cria uma cópia do elemento que vai ser retirado de sua posição para colocá-lo na posição desejada
    NODE* aux = NULL;
    aux = (NODE*) malloc (1*sizeof(NODE));
    aux = lista->raiz;

    //Marca a posição anterior à alterada, para manipular os ponteiros
    NODE* marcador = NULL;
    marcador = (NODE*) malloc (1*sizeof(NODE));
    marcador = lista->raiz;

    int i = 1;
    for(i = 1; i < posinicial; i++) aux = aux->prox;

    if(posinicial == 1) lista->raiz = lista->raiz->prox;
    else{
        for(i = 1; i < posinicial-1; i++) marcador = marcador->prox;
        //Caso a posição encontrada seja a última da fila, o próximo é setado como nulo.
        if(posinicial < lista->tam) marcador->prox = aux->prox;
        else marcador->prox = NULL;

        percorrerLista(&(lista->raiz), lista, marcador, posinicial-1, 1);
    }

    if(posfinal == 1){
        aux->prox = lista->raiz;
        lista->raiz = aux;
    }
    else{
        if(posfinal > lista->tam) posfinal = lista->tam;
        marcador = lista->raiz;
        for(i = 1; i < posfinal-1; i++) marcador = marcador->prox;
        aux->prox = marcador->prox;
        marcador->prox = aux;
        percorrerLista(&(lista->raiz), lista, marcador, posfinal-1, 1);
    }

    free(aux);
    free(marcador);
}

/*
Pega entradas para troca de posição da aba e chama a função de troca
Parâmetros: Lista
Retorno: Não há, mas a lista modifica internamente com posição trocada
*/
void alterarAba(LISTA* lista){

    char* titulo = NULL;
    titulo = getString();

    //Determina as posições iniciais e finais da troca
    int posfinal, posinicial;
    scanf("%d", &posfinal);
    if(posfinal > lista->tam) posfinal = lista->tam;
    posinicial = determinarPosInicial(lista, lista->raiz, titulo, 1);

    trocarAba(lista, posinicial, posfinal);
}

/*
Imprime todas as posições da lista
Parâmetros: Lista a ser impressa, no raiz
Não há retorno.
*/
void imprimirLista(LISTA* lista, NODE* no){
    if(no != NULL){
        printf("%s %s %.2d/%.2d %.2d:%.2d\n", no->titulo, no->URL, no->dia, no->mes, no->hora, no->minuto);
        imprimirLista(lista, no->prox);
    }
}

/*
Transforma a lista dinâmica em um vetor estático, para facilitar as operações. A lista não é alterada.
Parâmetros: Lista dinâmica
Retorno: Vetor de estrutura NODE igual a lista
*/
NODE** listaEmVetor(LISTA* lista){
    NODE** vetor = NULL;
    vetor = (NODE**) malloc ((lista->tam*2)*sizeof(NODE*));

    NODE* aux = NULL;
    aux = (NODE*) malloc (1*sizeof(NODE));
    aux = lista->raiz;

    int i = 0;
    for(i = 0; i < lista->tam; i++){
        vetor[i] = aux;
        aux = aux->prox;
    }

    free(aux);

    return vetor;
}

void imprimirVetor(NODE** vetor1, LISTA* lista){
    int i = 0;
    for(i = 0; i < 20; i++) {
        if(vetor1[i] != '\0') printf("Vetor[%d]: %s %s %.2d/%.2d %.2d:%.2d\n", i,
            vetor1[i]->titulo, vetor1[i]->URL, vetor1[i]->dia, vetor1[i]->mes, vetor1[i]->hora, vetor1[i]->minuto);
        else printf("Vetor[%d]: Vazio.\n", i);
    }
}

/*
    Shifta todas as posições a direita até um encontrar espaço vazio
    Parâmetros: Vetor a ser mudado, vetor com elemento a ser colocado, posição inicial da colisão
    Retorno: Vetor modificado.
*/
NODE** shiftarPos(NODE** vetorF, NODE** vetorI, int j, int i){
    int k = j;
    while(vetorF[k] != '\0') k++;
    for(; k > j; k--) vetorF[k] = vetorF[k-1];
    vetorF[j] = vetorI[i];

    return vetorF;
}

/*
Operação de radixSort
Caso haja colisão, se algarismo sendo comparado for menor que o colidido, shifta o colidido e todos os elementos a direita
até encontrar  um espaço vazio. Se for igual ou maior, procura o próximo espaço vazio à direita para inserir o novo elemento.
| 201 | 200 | 058 | 731 | 105 | 150 | 345 | 602 |
Coleta as unidades e coloca os números em seus índices
| 200 | 150 | 201 | 731 | 602 | 105 | 345 | 058 |
Coleta as dezenas e coloca os números em seus índices
| 200 | 201 | 602 | 105 | 731 | 345 | 150 | 058 |
Coleta as centenas e coloca os números em seus índices
| 058 | 105 | 150 | 200 | 201 | 345 | 602 | 731 |
Está ordenado!!

Para conseguir a casa da unidade é usado %10 (65 % 10 == 5)
Para conseguir a casa da dezena é usado /10 (65 / 10 == 6) (Sempre arredonda para baixo por ser inteiro)

No caso desse programa será ordenado por minuto, hora, dia e mês. Cada um desses valores tem unidades e dezenas.
Ao fazer radix sort para cada um deles, na ordem acima, as abas ficarão ordenadas com complexidade linear
Parâmetros: Lista, Operação que indica que variável será usada para ordenar.
Retorno: Não há, mas a lista modifica internamente ordenada pela variável indicada.
*/
LISTA* radixSort(LISTA* lista, int op){

    NODE** vetor1 = NULL;
    NODE** vetor2 = NULL;
    if(lista->tam >= 10) vetor2 = (NODE**) calloc (lista->tam*2, sizeof(NODE*));
    else vetor2 = (NODE**) calloc (20, sizeof(NODE*));
    int i = 0, j;
    int done = FALSE;
    int aux = 0;

    LISTA* lista2 = NULL;
    lista2 = (LISTA*) malloc (1*sizeof(LISTA));
    lista2->raiz = NULL;
    lista2->tam = 0;

    //Tranforma a lista em vetor estático para facilitar a operação
    vetor1 = listaEmVetor(lista);

    switch(op){
        //Ordenar por minuto
        case 1:
            //Primeiro 'ordenamos' pela casa das unidades
            for(i = 0; i < lista->tam; i++){
                aux = vetor1[i]->minuto % 10;
                //aux contém o índice onde vetor[i] deve ser posicionado
                if(vetor2[aux] == '\0') vetor2[aux] = vetor1[i];
                else{
                    //Uma manipulação de espaço será necessária
                    //Setamos j na próxima posição vazia
                    j = aux;
                    while(vetor2[j] != '\0'){
                        if(aux < (vetor2[j]->minuto % 10)){
                            vetor2 = shiftarPos(vetor2, vetor1, j, i);
                            done = TRUE;
                            break;
                        }
                        j++;
                    }
                    if(done == FALSE && vetor2[j] == '\0'){
                        vetor2[j] = vetor1[i];
                    }
                    done = FALSE;
                }
            }
            //Agora pela casa das dezenas
            free(vetor1);
            vetor1 = NULL;
            if(lista->tam >= 10) vetor1 = (NODE**) calloc ((lista->tam*2), sizeof(NODE*));
            else vetor1 = (NODE**) calloc (20, sizeof(NODE*));
            for(i = 0; i < lista->tam*2; i++){
                if(vetor2[i] != '\0'){
                    aux = (int) vetor2[i]->minuto / 10;
                    //aux contém o índice onde vetor[i] deve ser posicionado
                    if(vetor1[aux] == '\0') vetor1[aux] = vetor2[i];
                    else{
                        //Uma manipulação de espaço será necessária
                        //Setamos j na próxima posição vazia
                        j = aux;
                        while(vetor1[j] != '\0'){
                            if(aux < (int)(vetor1[j]->minuto / 10)){
                                vetor1 = shiftarPos(vetor1, vetor2, j, i);
                                done = TRUE;
                                break;
                            }
                            j++;
                        }
                        if(done == FALSE && vetor1[j] == '\0'){
                            vetor1[j] = vetor2[i];
                        }
                        done = FALSE;
                    }
                }
            }
            break;
        //Ordenar por hora
        case 2:
            for(i = 0; i < lista->tam; i++){
                aux = vetor1[i]->hora % 10;
                if(vetor2[aux] == '\0') vetor2[aux] = vetor1[i];
                else{
                    j = aux;
                    while(vetor2[j] != '\0'){
                        if(aux < (vetor2[j]->hora % 10)){
                            vetor2 = shiftarPos(vetor2, vetor1, j, i);
                            done = TRUE;
                            break;
                        }
                        j++;
                    }
                    if(done == FALSE && vetor2[j] == '\0'){
                        vetor2[j] = vetor1[i];
                    }
                    done = FALSE;
                }
            }
            free(vetor1);
            vetor1 = NULL;
            if(lista->tam >= 10) vetor1 = (NODE**) calloc ((lista->tam*2), sizeof(NODE*));
            else vetor1 = (NODE**) calloc (20, sizeof(NODE*));
            for(i = 0; i < lista->tam*2; i++){
                if(vetor2[i] != '\0'){
                    aux = (int) vetor2[i]->hora / 10;
                    if(vetor1[aux] == '\0') vetor1[aux] = vetor2[i];
                    else{
                        j = aux;
                        while(vetor1[j] != '\0'){
                            if(aux < (int)(vetor1[j]->hora / 10)){
                                vetor1 = shiftarPos(vetor1, vetor2, j, i);
                                done = TRUE;
                                break;
                            }
                            j++;
                        }
                        if(done == FALSE && vetor1[j] == '\0'){
                            vetor1[j] = vetor2[i];
                        }
                        done = FALSE;
                    }
                }
            }
            break;
        //Ordenar por dia
        case 3:
            for(i = 0; i < lista->tam; i++){
                aux = vetor1[i]->dia % 10;
                if(vetor2[aux] == '\0') vetor2[aux] = vetor1[i];
                else{
                    j = aux;
                    while(vetor2[j] != '\0'){
                        if(aux < (vetor2[j]->dia % 10)){
                            vetor2 = shiftarPos(vetor2, vetor1, j, i);
                            done = TRUE;
                            break;
                        }
                        j++;
                    }
                    if(done == FALSE && vetor2[j] == '\0'){
                        vetor2[j] = vetor1[i];
                    }
                    done = FALSE;
                }
            }
            free(vetor1);
            vetor1 = NULL;
            if(lista->tam >= 10) vetor1 = (NODE**) calloc ((lista->tam*2), sizeof(NODE*));
            else vetor1 = (NODE**) calloc (20, sizeof(NODE*));
            for(i = 0; i < lista->tam*2; i++){
                if(vetor2[i] != '\0'){
                    aux = (int) vetor2[i]->dia / 10;
                    if(vetor1[aux] == '\0') vetor1[aux] = vetor2[i];
                    else{
                        j = aux;
                        while(vetor1[j] != '\0'){
                            if(aux < (int)(vetor1[j]->dia / 10)){
                                vetor1 = shiftarPos(vetor1, vetor2, j, i);
                                done = TRUE;
                                break;
                            }
                            j++;
                        }
                        if(done == FALSE && vetor1[j] == '\0'){
                            vetor1[j] = vetor2[i];
                        }
                        done = FALSE;
                    }
                }
            }
            break;
        //Ordenar por mes
        case 4:
            for(i = 0; i < lista->tam; i++){
                aux = vetor1[i]->mes % 10;
                if(vetor2[aux] == '\0') vetor2[aux] = vetor1[i];
                else{
                    j = aux;
                    while(vetor2[j] != '\0'){
                        if(aux < (vetor2[j]->mes % 10)){
                            vetor2 = shiftarPos(vetor2, vetor1, j, i);
                            done = TRUE;
                            break;
                        }
                        j++;
                    }
                    if(done == FALSE && vetor2[j] == '\0'){
                        vetor2[j] = vetor1[i];
                    }
                    done = FALSE;
                }
            }
            free(vetor1);
            vetor1 = NULL;
            if(lista->tam >= 10) vetor1 = (NODE**) calloc ((lista->tam*2), sizeof(NODE*));
            else vetor1 = (NODE**) calloc (20, sizeof(NODE*));
            for(i = 0; i < lista->tam*2; i++){
                if(vetor2[i] != '\0'){
                    aux = (int) vetor2[i]->mes / 10;
                    if(vetor1[aux] == '\0') vetor1[aux] = vetor2[i];
                    else{
                        j = aux;
                        while(vetor1[j] != '\0'){
                            if(aux < (int)(vetor1[j]->mes / 10)){
                                vetor1 = shiftarPos(vetor1, vetor2, j, i);
                                done = TRUE;
                                break;
                            }
                            j++;
                        }
                        if(done == FALSE && vetor1[j] == '\0'){
                            vetor1[j] = vetor2[i];
                        }
                        done = FALSE;
                    }
                }
            }
            break;
    }
    //Agora temos nosso vetor de estrutura ordenados, vamos devolvê-lo para a lista auxiliar
    for(i = 0; i < 20 || i < (lista->tam*2); i++){
        if(vetor1[i] != '\0'){
            printf("vetor1[%d] = %s\n", i, vetor1[i]->titulo);
            adicionarAba(lista2, vetor1[i]);
            lista2->tam++;
        }else printf("vetor1[%d] = null\n", i);
    }

    free(vetor1);
    free(vetor2);
        
    return lista2;
}

LISTA* ordenarLista(LISTA* lista){
    
    lista = radixSort(lista, 1);
    lista = radixSort(lista, 2);
    printf("1:");
    imprimirLista(lista, lista->raiz);
    lista = radixSort(lista, 3);
    printf("2:");
    imprimirLista(lista, lista->raiz);
    lista = radixSort(lista, 4);
    printf("3:");
    imprimirLista(lista, lista->raiz);

    return lista;
}

int main(void){

    int op = 0;
    LISTA* lista = NULL;
    lista = (LISTA*) malloc (1*sizeof(LISTA));
    lista->raiz = NULL;
    lista->tam = 0;

    while(op != 5){
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                    inserir(lista);
                    lista->tam++;
                break;
            case 2:
                    alterarAba(lista);
                break;
            case 3:
                    lista = ordenarLista(lista);
                break;
            case 4:
                    imprimirLista(lista, lista->raiz);
                    printf("\n");
                break;
            case 5:
                    liberarLista(lista->raiz, lista);
                    free(lista);
                break;
        }
    }

    return 0;
}