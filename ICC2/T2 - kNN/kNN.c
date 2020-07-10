/*
T2 - ICC2 - 2018 - kNN

Rafael Olivier Cardoso
9436166
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct iris IRIS;

//A estrutura iris tem todos os dados a serem comparados
//O inteiro tamanho terá o tamanho da lista na primeira posição. Nas outras terá seu index.
struct iris{
    float sepalLenght;
    float sepalWidth;
    float petalLenght;
    float petalWidth;
    char* species;
    int tam;
};


/*
Função de debug: Imprime as listas do tipo IRIS
Parâmetro: Lista a ser imprimida
Retorno: Não há.
*/
void printList(IRIS* lista){
    int t;

    int i = 0;
    for(i = 0; i < lista[0].tam; i++){
        printf("sepalLenght: %f\n sepalWidth: %f\n petalLenght: %f\n petalWidth: %f\n species: %s\n tam: %d\n", 
            lista[i].sepalLenght, lista[i].sepalWidth, lista[i].petalLenght, lista[i].petalWidth, lista[i].species, lista[i].tam);
    }
}

/*
Pega através de arquivo a lista IRIS
Funciona para ambas as listas teste e treino
Parâmetro: Nome do arquivo onde está a lista
Retorno: Lista IRIS
*/
IRIS* getIrisList(char* fileName){

    FILE* fp;
    fp = fopen(fileName, "r");

    //A primeira linha do arquivo não contém nenhuma informação crítica e pode ser pulada
    char auxc = 1;
    while(auxc != '\n') auxc = getc(fp);

    IRIS* irisList = NULL;
    int i = 0, j = 0, k;
    int auxn = 0;
    float auxf = 1;

    while(!feof(fp)){

        fscanf(fp, "%f", &auxf);
        if(auxf != 0){
            i++;
            irisList = (IRIS*) realloc (irisList, i*sizeof(IRIS));
            irisList[i-1].sepalLenght = auxf;
            getc(fp); //Pega a virgula
            fscanf(fp, "%f", &irisList[i-1].sepalWidth);
            getc(fp); //Pega a virgula
            fscanf(fp, "%f", &irisList[i-1].petalLenght);
            getc(fp); //Pega a virgula
            fscanf(fp, "%f", &irisList[i-1].petalWidth);
            getc(fp); //Pega a virgula
            getc(fp); //Pega a primeira aspa
            irisList[i-1].species = NULL;
            do{
                auxc = getc(fp);
                if(auxc > 64 && auxc < 123 && !feof(fp)){
                    j++;
                    irisList[i-1].species = (char*) realloc (irisList[i-1].species, j*sizeof(char));
                    irisList[i-1].species[j-1] = auxc;
                }
            }while(auxc != '"' && !feof(fp));
            getc(fp);
            j++;
            irisList[i-1].species = (char*) realloc (irisList[i-1].species, j*sizeof(char));
            irisList[i-1].species[j-1] = '\0';
            j = 0;
            irisList[i-1].tam = i-1;
        }
    }

    irisList[0].tam = i-1;

    return irisList;
}

/*
Pega a distância entre o ponto vermelho e o ponto a ser comparado
Parâmetros: Lista de treino Iris, Lista de teste Iris, index de cada uma das posições a serem comparados
Retorno: Distância entre os dois pontos. 
*/
double getDistance(IRIS* trainIrisList, IRIS* testIrisList, int testIndex, int trainIndex){

    //root((a1 - a2)^2 + (b1 - b2)^2 + (c1 - c2)^2 + (d1 - d2)^2) = distance
    //       = a            =b             =c            =d
    double a, b, c, d;
    a = trainIrisList[trainIndex].sepalLenght - testIrisList[testIndex].sepalLenght;
    a = pow(a, 2.0);
    b = trainIrisList[trainIndex].sepalWidth - testIrisList[testIndex].sepalWidth;
    b = pow(b, 2.0);
    c = trainIrisList[trainIndex].petalLenght - testIrisList[testIndex].petalLenght;
    c = pow(c, 2.0);
    d = trainIrisList[trainIndex].petalWidth - testIrisList[testIndex].petalWidth;
    d = pow(d, 2.0);

    a = a + b + c + d;

    double distance = sqrt(a);

    return distance;
}

/*
Pega os índices das menores distâncias na lista de treino
Parâmetros: Ambas as listas de treino e teste. Quantidade de flores mais próximas a serem comparadas. Index da flor da lista de teste.
Retorno: Lista de inteiros com os índices das menores distâncias.
*/
int* getLeastDistances(IRIS* trainIrisList, IRIS* testIrisList, int k, int testIndex){

    //Lista das distâncias do caso de teste sendo avaliado atualmente
    //Contém a distância de cada tipo de flor
    double* distanceList = NULL;
    distanceList = (double*) malloc (trainIrisList[0].tam * sizeof(double));

    int i = 0, j = 0, index = 0;
    for(i = 0; i < trainIrisList[0].tam; i++){
        distanceList[i] = getDistance(trainIrisList, testIrisList, testIndex, i);
        //printf("%lf\n", distanceList[i]);
    }
    //printf("\n");

    //compara as distancias e seleciona as k mais proximas (menores)
    int* leastDistanceIndexList = NULL;
    leastDistanceIndexList = (int*) malloc (k * sizeof(int));

    double aux;
    for(i = 0; i < k; i++){
        aux = 999999; //Número grande para garantir que haverá um menor na lista de distâncias
        for(j = 0; j < trainIrisList[0].tam; j++){
            if(distanceList[j] < aux){
                aux = distanceList[j];  //Atualiza o auxiliar com a menor distancia
                index = j;              //Atualiza o index para apagar essa distância depois e evitar repetições
            }
        }
        leastDistanceIndexList[i] = index;     //Adiciona a posição da menor distancia na lista
        distanceList[index] = 999999;   //Apaga a distância usada
    }

    //Linhas para debugg. Indicam as menores distâncias entre as flores.
    //for(i = 0; i < k; i++) printf("Menor Distância %d: %d\n", i, leastDistanceIndexList[i]);
    //printf("\n");

    return leastDistanceIndexList;
}


/*
Pega o tipo mais comum encontrado nas k flores mais próximas
Parâmetros: Vetor com as menores distâncias, Lista Iris de treino, Tamanho do vetor com as menores distâncias
Retorno: String com o tipo mais comum (ou mais próximo no caso de empate) de flor.
*/
char* findIrisType(int* leastDistanceVector, IRIS* trainIrisList, int k){

    int i = 0;
    char* irisType = NULL;
    irisType = (char*) malloc (20*sizeof(char));
    int orderList[k];   //0 = versicolor, 1 = setosa, 2 = virginica. Mantém a ordem no caso de empate.

    int versicolor = 0, setosa = 0, virginica = 0;
    for(i = 0; i < k; i++){
        strcpy(irisType, trainIrisList[leastDistanceVector[i]].species);
        if(strcmp(irisType, "versicolor") == 0){
            versicolor++;
            orderList[k] = 0;
        }
        if(strcmp(irisType, "setosa") == 0){
            setosa++;
            orderList[k] = 1;
        }
        if(strcmp(irisType, "virginica") == 0){
            virginica++;
            orderList[k] = 2;
        }
    }
    if(versicolor > setosa && versicolor > virginica) return "versicolor";
    if(setosa > versicolor && setosa > virginica) return "setosa";
    if(virginica > setosa && virginica > versicolor) return "virginica";

    //Se ainda não retornou, houve um empate...
    for(i = 0; i < k; i++){
        if(orderList[k] = 0){
            if(versicolor == setosa || versicolor == virginica) return "versicolor";
        }
        if(orderList[k] = 1){
            if(versicolor == setosa || setosa == virginica) return "setosa";
        }
        if(orderList[k] = 2){
            if(virginica == setosa || versicolor == virginica) return "virginica";
        }
    }

    //Caso não tenha retornado, algum erro ocorreu;
    return "Erro";
}

/*
Inicia o algoritmo kNN. Durante essa função várias outras serão chamadas.
Parâmetros: Listas IRIS a serem comparadas e número das k flores mais próximas.
Retorno: Não há retorno, mas imprime na tela cada caso e a taxa de acerto do algoritmo.
*/
void startkNN(IRIS* trainIrisList, IRIS* testIrisList, int k){
    
    /*
    Matriz das posições das menores distâncias em trainIrisList, 
    cada vetor tem tamanho k, e terá contido as posições das k menores distâncias.
    Para k = 3 e número de testes = 2.
    | 1 | 2 | 3 |
    | 4 | 5 | 2 |
    */
    int** leastDistanceIndexMatrix = NULL;

    //Alocação dinâmica de espaço
    int i = 0;
    leastDistanceIndexMatrix = (int**) malloc (testIrisList[0].tam * sizeof(int*));
    for(i=0; i < testIrisList[0].tam; i++){
        leastDistanceIndexMatrix[i] = (int*) malloc (k * sizeof(int));
    }

    for(i = 0; i < testIrisList[0].tam; i++){
        leastDistanceIndexMatrix[i] = getLeastDistances(trainIrisList, testIrisList, k, i);
    }

    int acerto = 0, erro = 0;
    int size;

    char* irisType = NULL;
    irisType = (char*) malloc (20*sizeof(char));
    for(i = 0; i < testIrisList[0].tam; i++){
        irisType = findIrisType(leastDistanceIndexMatrix[i], trainIrisList, k);
        printf("%s ", irisType);
        printf("%s\n", testIrisList[i].species);
        if(strcmp(irisType, testIrisList[i].species) == 0) acerto++;
        else{
            erro++;
        }
    }

    //printf("Acertos: %d Erros: %d", acerto, erro);

    //Total - 1         |  3  -  1          3x = 2        x = Acerto/Total
    //Acerto - x        |  2  -  x          x = 2/3;
    int total = acerto+erro;
    float taxa = (float)acerto/(float)total;
    printf("%.4f", taxa);

}

int main (int argc, char* argv[]){

    //Leituras de entrada

    char* trainFileName = NULL;
    char* testFileName = NULL;

    trainFileName = (char*) malloc (20*sizeof(char));
    testFileName = (char*) malloc (20*sizeof(char));

    scanf("%s", trainFileName);
    scanf("%s", testFileName);

    int k = 0;
    scanf("%d", &k);

    //Alocar todos os dados nos arquivos em listas de estruturas Iris
    IRIS* trainIrisList = NULL;
    IRIS* testIrisList = NULL;

    trainIrisList = getIrisList(trainFileName);
    if(k < 1 || k >= trainIrisList[0].tam){
        printf("k is invalid\n");
        return 0;
    }
    testIrisList = getIrisList(testFileName);

    //Inicio do kNN
    startkNN(trainIrisList, testIrisList, k);

    //Liberação de espaço alocado
    free(trainFileName);
    free(testFileName);
    free(trainIrisList);
    free(testIrisList);

    return 0;
}