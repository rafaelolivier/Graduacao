all: compile

compile:
	gcc -o arquivosProjeto main.c otherfunctions.c escreverTela2.c trab1functions.c trab2functions.c binfunctions.c -std=c99 -g

run: compile
	valgrind ./arquivosProjeto
