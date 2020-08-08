import math
import time
from queue import *
from copy import *
#fills a matrix with 'whatuwant'
def filledList(h,w, whatuwant):
    l=[]
    for i in range(h):
        l.append([whatuwant for j in range(w)])
    return l
#prints a matrix
def printM(m):
    for i in m:
        print(i)

#prints path over matrix
def pathovrmatrix(matrix, path):
    m = deepcopy(matrix)
    for i in range(len(path)):
        if ( m[path[i][0]][path[i][1]] == '*' ):
            m[path[i][0]][path[i][1]] = '@'
    printM(m)

#convert prev tuple list to list of lists
def prev2list(m, s, e):
    l=[]
    actual = e
    l.insert(0, tuple(actual))
    while (actual != s):
        actual = m[actual[0]][actual[1]]
        l.insert(0, tuple(actual))
    return l

def tuple2list(tup):
    l = []
    for i in tup:
        l.append(list(i))
    return l
#calc dist based on consecutive points
def prev2dist(prev):
    dist = 0.0
    for i in range(len(prev)-1):
        dist = dist + math.sqrt( math.pow(prev[i+1][0] - prev[i][0],2) + math.pow(prev[i+1][1] - prev[i][1],2))
    return dist

#runs BFS algorithm
def BFS(m,i,j,start,end):
    flag = filledList(i,j, False)
    prev = filledList(i,j,[-1,-1])

    q = Queue()
    flag[start[0]][start[1]]=True
    q.put(list(start))

    while( not q.empty() ):
        v = q.get()
        # checking every move possible
        for i_offset in range(-1,2):
            if (i_offset + v[0] > -1 and \
                    i_offset + v[0] < i):
                #if x offset is possible, checks y
                for j_offset in range(-1,2):
                    if (j_offset + v[1] > -1 and \
                            j_offset + v[1] < j):
                    ##if both are possible ...
                        if (flag[i_offset+v[0]][j_offset+v[1]] == False and\
                                m[i_offset+v[0]][j_offset+v[1]] != "-"):
                            flag[i_offset+v[0]][j_offset+v[1]] = True
                            prev[i_offset+v[0]][j_offset+v[1]] = v
                            q.put([i_offset+v[0],j_offset+v[1]])
    path = prev2list(prev, start, end)
    dist = prev2dist(path)

    pathovrmatrix(m, tuple2list(path))

    print("stepcounter:", len(path)-1)
    print("distance:", dist)
    print("path:", path)

#runs DFS algorithm
def DFS(m,i,j,start,end):
    flag = filledList(i,j, False)
    prev = filledList(i,j,[-1,-1])

    q = []
    flag[start[0]][start[1]]=True
    q.append(list(start))

    while( q != []):
        v = q.pop()
        # checking every move possible
        for i_offset in range(-1,2):
            if (i_offset + v[0] > -1 and \
                    i_offset + v[0] < i):
                #if x offset is possible, checks y
                for j_offset in range(-1,2):
                    if (j_offset + v[1] > -1 and \
                            j_offset + v[1] < j):
                    ##if both are possible ...
                        if (flag[i_offset+v[0]][j_offset+v[1]] == False and\
                                m[i_offset+v[0]][j_offset+v[1]] != "-"):
                            flag[i_offset+v[0]][j_offset+v[1]] = True
                            prev[i_offset+v[0]][j_offset+v[1]] = v
                            q.append([i_offset+v[0],j_offset+v[1]])

    path = prev2list(prev, start, end)
    dist = prev2dist(path)
    print("stepcounter:", len(path)-1)
    print("distance:", dist)
    print("path:", path)

    pathovrmatrix(m, list(path))


#Calcula a distancia entre as coordenadas x, y e o fim
def getDist(x, y, end):
    distanceTotal = 0
    distanceX = end[0] - x
    distanceY = end[1] - y

    if(distanceX < 0):
        distanceX = 0 - distanceX
    if(distanceY < 0):
        distanceY = 0 - distanceY

    if(distanceX > distanceY):
        distanceTotal = distanceY * math.sqrt(2)
        distanceX = distanceX - distanceY
        distanceTotal = distanceTotal + distanceX
    else:
        distanceTotal = distanceX * math.sqrt(2)
        distanceY = distanceY - distanceX
        distanceTotal = distanceTotal + distanceY

    return distanceTotal

# best1st resolve o problema procurando apenas o próximo melhor passo
# A solução não será necessariamente ótima
# Parâmetros: Tabuleiro(Matriz), Altura(inteiro), Largura(inteiro), Começo(Tupla), Fim(Tupla)
# Retorna: Lista com os passos dados
def best1st(m,h,w, start, trueend):

    curr = [start[0], start[1]] #posição atual
    end = [trueend[0], trueend[1]] #final em forma de lista
    path = [] #Lista com os passos percorridos
    path.append((curr[0], curr[1]))
    stepcounter = 0 #contador de passos
    distance = 0 #contador de distâncias

    visited = [[0 for x in range(w)] for y in range(h)] #Tratamento de Repetição

    while curr != end:
        stepcounter = stepcounter+1 #incrementa o número de passos
        aux = 0 #indica qual é a posição da lista no menor elemento válido a ser testado
        bolFound = 0    #indica se o passo foi válido

        # Lista das distâncias das posições adjacentes em relação ao objetivo
        # Calcula as distâncias das posições adjacentes, então testa da menor para a maior
        # Como a busca é gulosa, só o próximo passo será calculado
        distanceList = [getDist(curr[0]+1, curr[1]+1, end), getDist(curr[0], curr[1]+1, end), getDist(curr[0]-1, curr[1]+1, end), getDist(curr[0]-1, curr[1], end), getDist(curr[0]-1, curr[1]-1, end), getDist(curr[0], curr[1]-1, end), getDist(curr[0]+1, curr[1]-1, end), getDist(curr[0]+1, curr[1], end), getDist(curr[0], curr[1], end)]
        while bolFound != 1:

            #Pega a menor distância válida. 99999999 indica uma posição ruim que já foi testada
            #Por isso, o tabuleiro não pode ter distâncias maiores que 99999999
            minDist = 99999999
            for i in range(9):
                if(minDist >= distanceList[i]):
                    minDist = distanceList[i]
                    aux = i
            # As casas são marcadas como
            #   | 4 | 3 | 2 |
            #   | 5 | 8 | 1 |
            #   | 6 | 7 | 0 |
            # Aux marca a casa com menor distância do fim, válida ou ainda não testada

            #Os testes que são feitos para ver se a casa é válida são:
            #Verificar se não vai sair do tabuleiro e verificar se não contém - no local
            #Também verifica se a casa já não foi visitada anteriormente e não encontrou boas soluções
            #Caso uma dessas condições seja verdadeira, marca como inválida com 99999999
            if (aux == 0):
                if not(curr[0]+1 > h-1) and not(curr[1]+1 > w-1) and not('-' in m[curr[0]+1][curr[1]+1]) and not(visited[curr[0]+1][curr[1]+1] == 1):
                    curr[0] = curr[0]+1
                    curr[1] = curr[1]+1
                    distance = distance + math.sqrt(2)
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 1):
                if not(curr[1]+1 > w-1) and not('-' in m[curr[0]][curr[1]+1]) and not(visited[curr[0]][curr[1]+1] == 1):
                    curr[1] = curr[1]+1
                    distance = distance + 1
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 2):
                if not(curr[0]-1 < 0) and not(curr[1]+1 > w-1) and not('-' in m[curr[0]-1][curr[1]+1]) and not(visited[curr[0]-1][curr[1]+1] == 1):
                    curr[0] = curr[0]-1
                    curr[1] = curr[1]+1
                    distance = distance + math.sqrt(2)
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 3):
                if not(curr[0]-1 < 0) and not('-' in m[curr[0]-1][curr[1]]) and not(visited[curr[0]-1][curr[1]] == 1):
                    curr[0] = curr[0]-1
                    distance = distance + 1
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 4):
                if not(curr[0]-1 < 0) and not(curr[1]-1 < 0) and not('-' in m[curr[0]-1][curr[1]-1]) and not(visited[curr[0]-1][curr[1]-1] == 1):
                    curr[0] = curr[0]-1
                    curr[1] = curr[1]-1
                    distance = distance + math.sqrt(2)
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 5):
                if not(curr[1]-1 < 0) and not('-' in m[curr[0]][curr[1]-1]) and not(visited[curr[0]][curr[1]-1] == 1):
                    curr[1] = curr[1]-1
                    distance = distance + 1
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 6):
                if not(curr[0]+1 > h-1) and not(curr[1]-1 < 0) and not('-' in m[curr[0]+1][curr[1]-1]) and not(visited[curr[0]+1][curr[1]-1] == 1):
                    curr[0] = curr[0]+1
                    curr[1] = curr[1]-1
                    distance = distance + math.sqrt(2)
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            if(aux == 7):
                if not(curr[0]+1 > h-1) and not('-' in m[curr[0]+1][curr[1]]) and not(visited[curr[0]+1][curr[1]] == 1):
                    curr[0] = curr[0]+1
                    distance = distance + 1
                    path.append((curr[0], curr[1]))
                    bolFound = 1
                else:
                    distanceList[aux] = 99999999
            #Se aux == 8, a casa onde está é a mais perto de todas as adjacentes válidas
            #Isso significa que essa casa não é interessante e forçaremos o programa a não voltar mais aqui para evitar loops
            if(aux == 8):
                distanceList[aux] = 99999999
                visited[curr[0]][curr[1]] = 1

    print("stepcounter: ", end = '')
    print(stepcounter)
    print("distance: ", end = '')
    print(distance)
    print("path: ", end = '')
    print(path)

    pathovrmatrix(m, list(path))

    return path


def astar(matrix, row, col, sp, ep):
    curr = sp  # posição atual
    end = ep  # final em forma de lista
    path = []  # Lista com os passos percorridos
    path.append(curr)
    stepcounter = 0  # contador de passos
    distance = 0  # contador de distâncias
    explored = set()

    visited = [[0 for x in range(row)] for y in range(col)]  # Tratamento de Repetição
    dist = [row][col]
    for r in range(row):
        for c in range(col):
            dist[r][c] = abs(r - ep[0]) + abs(c - ep(1))


    while curr != end:
        stepcounter = stepcounter + 1



matrix=[]
height,width=map(int, input().split())
for i in range(height):
    matrix.append(list(input()))

for i in range(height):
    try:
        start = (i, matrix[i].index('#'))
    except:
        pass

for i in range(height):
    try:
        end = (i, matrix[i].index('$'))
    except:
        pass
print("BFS")
BFS(matrix, height, width, list(start), list(end));print()
print("DFS")
DFS(matrix, height, width, list(start), list(end));print()
print("BEST-FIRST")
best1st(matrix, height, width, start, end)
