#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./start-menu.h"
#include "./../graphic/bike.h"
#include "./../utils/text-tools.h"
#include "./navigation.h"

/* définititon des variables*/

/* définititon des fonctions */
float basey0 = 0.0;
float basey1 = 1.0;

void vClavier_startmenu(unsigned char key, int x, int y);
void vClavierSpecial_startmenu(int key, int x, int y);
void vDisplay_startmenu();
void displayStartMenu();

GLuint texture;
void windowMenu(GLuint tex) {
    texture = tex;
    glutDisplayFunc(vDisplay_startmenu);
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
        setMainCurrentWindow(1); // todo changer le hardcode
    }
}

void vDisplay_startmenu() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    basey0 += 0.00005;
    basey1 += 0.00005;
    glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2f(-0.9539f, basey0); glVertex2f(-1.005, -1); // en bas a gauche
            glTexCoord2f(-0.9539f, basey1); glVertex2f(-1.005, 1); // au dessus à gauche
            glTexCoord2f(0.0461f, basey1); glVertex2f(1.096, 1); // au dessus à droite
            glTexCoord2f(0.0461f, basey0); glVertex2f(1.096, -1); // en bas à droite
        glEnd();
    glPopMatrix();
    displayStartMenu();
    glutPostRedisplay();
    glutSwapBuffers(); 

}

void displayStartMenu() {
    char option1 [] = "Continuer la partie en cours";
    char option2 [] = "Commencer une nouvelle partie";
    char option3 [] = "Configurer le jeu";
    char option4 [] = "Lire les règles du jeu";
    char option5 [] = "Highscores";
    char option6 [] = "Quitter";
    writeOnWindow(-0.5, 0.5, option1, strlen(option1));
    writeOnWindow(-0.5, 0.4, option2, strlen(option2));
    writeOnWindow(-0.5, 0.3, option3, strlen(option3));
    writeOnWindow(-0.5, 0.2, option4, strlen(option4));
    writeOnWindow(-0.5, 0.1, option5, strlen(option5));
    writeOnWindow(-0.5, 0.0, option6, strlen(option6));
}

