#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./navigation.h"
#include "./start-menu.h"
#include "./../movement/square.h" // TODO : pourquoi je dois importer square.h pour faire fonctionner textTools.h alors que textTools.h importe lui même square.h
#include "./../utils/textTools.h"

/* définititon des variables*/
int numberWindowGame;

/* définititon des fonctions */

void vClavier_startmenu(unsigned char key, int x, int y);
void vClavierSpecial_startmenu(int key, int x, int y);
void vDisplay_startmenu();
void vReshape_startmenu();

void windowMenu(int numeroWindows[]) {
    glutInitWindowSize(WIDTH_STARTMENU, HEIGHT_STARTMENU);
	glutInitWindowPosition(XWINDOWPOSITION_STARTMENU, YWINDOWPOSITION_STARTMENU);
	numeroWindows[0] = glutCreateWindow("Menu");
    numberWindowGame = numeroWindows[1];
	glutDisplayFunc(vDisplay_startmenu);
	glutReshapeFunc(vReshape_startmenu);
    glutSpecialFunc(vClavierSpecial_startmenu); // up and down
	glutKeyboardFunc(vClavier_startmenu); // enter
}

void vClavierSpecial_startmenu(int key, int x, int y) 
{
	switch (key){
        case GLUT_KEY_UP:
        // TODO : change current selected window
            break;

        case GLUT_KEY_DOWN:
        break;

        default:
        break;
    }
}

void vClavier_startmenu(unsigned char key, int x, int y) {
    if (key == 13) {
        glutHideWindow();
        //glutDestroyWindow(glutGetWindow());
        glutSetWindow(numberWindowGame);
        glutShowWindow();
        setCurrentMainWindow(numberWindowGame);
    }
}

void vDisplay_startmenu() {
    char text [] = "Press ENTER to start the game";
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    writeOnWindow(-1, 0.9, text, strlen(text));
    glLoadIdentity();
    glutPostRedisplay();
    glutSwapBuffers(); 
}

void vReshape_startmenu() {

}