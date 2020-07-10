/*Trabalho 2 de computação gráfica
	Guilherme Correa Fernandes	9278174
	Rafael Olivier Cardoso 		9436166
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
/*
 * 	Definição do tamanho da janela de exibição.
 * */
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

float rotationX = 0;
float rotationY = 0;
double cameraDistance = 3.0;
int figure = 1;
int perspective = 0;
float scale = 1;
double mouseX = 0;
double mouseY = 0;
int rotationFlag = 0;
double translateX = 0;
double translateY = 0;
double translateZ = 0;
int shading = 0;

void display();

void init(){
	glClearColor(0, 0, 0, 0);
}

/*
 *	Reseta as transformações.
 * */

void resetView(){
	rotationX = 0;
	rotationY = 0;
	cameraDistance = 3.0;
	perspective = 0;
}
/*
 *	Altera a variavel de perspectiva (para alterar entre perspectiva e ortogonal)
 * */

void changePerspective(){
	if (perspective == 0)
		perspective = 1;
	else perspective = 0;
}

/*
 *	Função que cuida dos eventos quando as teclas são pressionadas
 * */

void keyPressEvent(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			translateY +=0.01;
			break;
		case 's':
			translateY -=0.01;
			break;
		case 'd':
			translateX += 0.01;
			break;
		case 'a':
			translateX -=0.01;
			break;
		case 'q':
			translateZ +=0.01;
			break;
		case 'e':
			translateZ -=0.01;
			break;
		case 'r':
			resetView();
			break;
		case 'p':
			changePerspective();
			break;
		case 'f':
			shading = 0;
			break;
		case 'g':
			shading = 1;
			break;
	}
	display();
}

/*
 *	Função que desenha um cubo de lado 1
 * */

void drawCube(){
	float x = 1.0f;

	glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidCube(2);

}

/*
 *	Função para desenhar uma piramide de lado 1.
 * */

void drawPyramid (){

	glScalef(2.0f, 2.0f, 2.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glutSolidTetrahedron();
	glScalef(0.5f, 0.5f, 0.5f);
}
/*
 *	Função que chama a função padrão Glut para desenhar um Torus
 * */

void drawTorus (){
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTorus(0.5, 1.0, 30, 30);
}

/*
 *	Função que chama a função padrão Glut para desenhar um bule
 * */
void drawTeapot(){
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTeapot(1.0);
}

/*
 *	Função que chama a função padrão Glut para desenhar um icosaedro
 * */
void drawIcosahedron(){
	glColor3f(1.0, 0.0, 1.0);
	glutSolidIcosahedron();
}

/*
 *	Função para desenhar os objetos
 * */
void display(){

	float x = 1.0f;
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, SCREEN_HEIGHT/5, SCREEN_WIDTH/5 * 4, SCREEN_HEIGHT/5 * 4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	if(shading == 0)
		glShadeModel(GL_FLAT);
	else if(shading == 1)
		glShadeModel(GL_SMOOTH);
	glScalef(scale, scale ,scale);
	glTranslatef(translateX, translateY, translateZ);
	//Altera perspectiva
	if(perspective == 0)
		glFrustum(-1.0f, 1.0f, -1.0f, 0.9f, 1.0f, 10000.0f);
	else
		glOrtho(-2.0f, 2.0f, -2.0f, 1.9f, 1.0f, 10000.0f);
	gluLookAt(0, 0, cameraDistance, 0, 0, -1, 0, 1, 0);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	//Altera a figura desenhada
	if(figure == 1)
		drawCube();
	else if(figure == 2)
		drawPyramid();
	else if(figure == 3)
		drawTorus();
	else if(figure == 4)
		drawTeapot();
	else if(figure == 5)
		drawIcosahedron();
	//Desenha as figuras menores (botões) em outras viewports/
	glLoadIdentity();
	glScalef(0.5,0.5,0.5);
	glViewport(0, 0, SCREEN_WIDTH/5, SCREEN_HEIGHT/5);
	drawCube();
	glViewport(SCREEN_WIDTH/5, 0, SCREEN_WIDTH/5, SCREEN_HEIGHT/5);
	drawPyramid();
	glViewport(SCREEN_WIDTH/5*2, 0, SCREEN_WIDTH/5, SCREEN_HEIGHT/5);
	drawTorus();
	glViewport(SCREEN_WIDTH/5*3, 0, SCREEN_WIDTH/5, SCREEN_HEIGHT/5);
	drawTeapot();
	glViewport(SCREEN_WIDTH/5*4, 0, SCREEN_WIDTH/5, SCREEN_HEIGHT/5);
	drawIcosahedron();

	glPushMatrix();

	glFlush();
	glutSwapBuffers();
}

/*
 * 	Função para tratar os eventos quando um botão do mouse é pressionado.
 */

void onMouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		rotationFlag = 1;
		if(y > SCREEN_HEIGHT/5 * 4){
			if(x < SCREEN_WIDTH/5)
				figure = 1;
			else if(x < SCREEN_WIDTH/5 * 2)
				figure = 2;
			else if(x < SCREEN_WIDTH/5 * 3)
				figure = 3;
			else if(x < SCREEN_WIDTH/5 * 4)
				figure = 4;
			else if(x < SCREEN_WIDTH/5 * 5)
				figure = 5;
		}
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		rotationFlag = 0;
	else if(button == 3)
		scale -= 0.01;
	else if(button == 4)
		scale += 0.01;
	display();
}

/*
 *	Função para tratar o movimento do mouse
 */

void onMouseMotion(int x, int y){

if(rotationFlag == 1){
		if(x > mouseX)
			rotationY += 0.2;
		if(x < mouseX)
			rotationY -= 0.2;
		if(y > mouseY)
			rotationX += 0.2;
		if(y < mouseY)
			rotationX -= 0.2;
	}
	mouseX = x;
	mouseY = y;
	display();
}

/*
 *	Função principal: Inicializa o opengl e cria a janela, além de definir as funções para tratamento de eventos.
 * */

int main (int argc, char * argv[]){

	GLfloat light_pos[] = {1.0, 2.0, 3.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};

	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutCreateWindow("Trabalho 2");
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressEvent);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMotion);


	glutMainLoop();


};
