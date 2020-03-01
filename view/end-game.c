#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./end-game.h"
#include "./../movement/square.h"
#include "./../graphic/enemy.h"
/* définititon des variables*/
int numberWindowStartMenu;

/* définititon des fonctions */

void vClavier_endgame(unsigned char key, int x, int y);
void vClavierSpecial_endgame(int key, int x, int y);
void vDisplay_endgame();
void vReshape_endgame();
void drawSquare_endgame();
void initEndGame();

void windowEndGame(int numeroWindows[]) {
    glutInitWindowSize(WIDTH_ENDGAME, HEIGHT_ENDGAME);
	glutInitWindowPosition(XWINDOWPOSITION_ENDGAME, YWINDOWPOSITION_ENDGAME);
	numeroWindows[2] = glutCreateWindow("Bike vs Cars - END");
    numberWindowStartMenu = 3; // TODO : changer ce hard code
	glutDisplayFunc(vDisplay_endgame);
	glutReshapeFunc(vReshape_endgame);
    glutSpecialFunc(vClavierSpecial_endgame); // up and down
	glutKeyboardFunc(vClavier_endgame); // enter
    initEndGame();
}

void initEndGame() {
    glutHideWindow();
}

void vClavierSpecial_endgame(int key, int x, int y) 
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

void vClavier_endgame(unsigned char key, int x, int y) {
    if (key == 13) {
        glutHideWindow();
        glutSetWindow(numberWindowStartMenu); // retour au menu principal
        //glutDestroyWindow(glutGetWindow());
    }
}
/*
* Affiche la scene finale du jeu mais sans les commandes pour déplacer le carré
* Les nouvelles commandes permettent de recommencer une partie ou de revenir au menu de départ
*/
void vDisplay_endgame() {
    glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
        glLoadIdentity();
        glPushMatrix();// sauvegarde l'état actuel de la matrice
            glTranslatef(_square.position.x, _square.position.y, _square.position.z);
            drawSquare_endgame();
        glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
        glPushMatrix();
            glTranslatef(_enemy.position.x, _enemy.position.y, _enemy.position.z);
            drawEnemy();
        glPopMatrix();
        glutPostRedisplay();
        glutSwapBuffers(); // permute buffers
}

void vReshape_endgame() {

}

void drawSquare_endgame(){
    glColor4f(1.0, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.1, 0.2);
        glVertex2f(0.1, 0.2);
        glVertex2f(0.1, -0.2);
    glEnd();
}