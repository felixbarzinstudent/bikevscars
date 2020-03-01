#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./start-menu.h"
#include "./../movement/square.h" // TODO : pourquoi je dois importer square.h pour faire fonctionner textTools.h alors que textTools.h importe lui même square.h
#include "./../utils/textTools.h"

/* définititon des variables*/
int windowGame;

/* définititon des fonctions */

void vClavier(unsigned char key, int x, int y);
void vClavierSpecial(int key, int x, int y);
void vDisplay();
void vReshape();

void windowMenu(int numeroWindows[]) {
    glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(XWINDOWPOSITION, YWINDOWPOSITION);
	numeroWindows[0] = glutCreateWindow("Menu");
    windowGame = numeroWindows[1];
	glutDisplayFunc(vDisplay);
	glutReshapeFunc(vReshape);
    glutSpecialFunc(vClavierSpecial); // up and down
	glutKeyboardFunc(vClavier); // enter
}

void vClavierSpecial(int key, int x, int y) 
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

void vClavier(unsigned char key, int x, int y) {
    if (key == 13) {
        glutHideWindow();
        glutSetWindow(windowGame);
    }
}

void vDisplay() {
    char text [] = "Press ENTER to start the game";
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    writeOnWindow(-1, 0.9, text, strlen(text));
    glLoadIdentity();
    glutPostRedisplay();
    glutSwapBuffers(); 
}

void vReshape() {

}