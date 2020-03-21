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

int activeOption = 2;
int activeOptionMenuConfigurer = 1;

int activeMenu = 1;

void vClavier_startmenu(unsigned char key, int x, int y);
void vClavierSpecial_startmenu(int key, int x, int y);
void vDisplay_startmenu();
void displayStartMenu();
void displayStartMenuConfigurer();

GLuint texture;
void windowMenu(GLuint tex) {
    texture = tex;
    glutDisplayFunc(vDisplay_startmenu);
    glutSpecialFunc(vClavierSpecial_startmenu); // up and down
    glutKeyboardFunc(vClavier_startmenu); // enter
}

void vClavierSpecial_startmenu(int key, int x, int y) 
{
    if(activeMenu == 1) { // menu de base
        switch (key){
            case GLUT_KEY_UP:
                activeOption -= 1;
                if(activeOption < 1)
                    activeOption = 6;
                break;

            case GLUT_KEY_DOWN:
                activeOption += 1;
                if(activeOption > 6)
                    activeOption = 1;
                break;

            default:
            break;
        }
    } else if (activeMenu == 2) {
        switch (key){
            case GLUT_KEY_UP:
                activeOptionMenuConfigurer -= 1;
                if(activeOptionMenuConfigurer < 1)
                    activeOptionMenuConfigurer = 4;
                break;

            case GLUT_KEY_DOWN:
                activeOptionMenuConfigurer += 1;
                if(activeOptionMenuConfigurer > 4)
                    activeOptionMenuConfigurer = 1;
                break;

            default:
            break;
        }
    }
}

void vClavier_startmenu(unsigned char key, int x, int y) {
    if (activeMenu == 1) { // Menu de base
        if (key == 13) {
            if (activeOption == 1) {
                setMainCurrentWindow(1);
                _startMenuActiveOption = 1; // pour dire a la page de jeu qu'on veut reprendre au dernier checkpoint
            }
            else if (activeOption == 2)
                setMainCurrentWindow(1); // todo changer le hardcode 1 -> jeu
            else if (activeOption == 3)
                activeMenu = 2;
        }
    } else if (activeMenu == 2) {
        if (key == 13) {
            if (activeOptionMenuConfigurer == 1) {
                _difficulty = 1;
            } else if (activeOptionMenuConfigurer == 2) {
                _difficulty = 3;
            } else if (activeOptionMenuConfigurer == 3) {
                _difficulty = 5;
            } 

            activeMenu = 1;
        }
    }
}

void vDisplay_startmenu() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    basey0 += 0.00005;
    basey1 += 0.00005;
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(-0.9539f, basey0); glVertex2f(-1.005, -1); // en bas a gauche
            glTexCoord2f(-0.9539f, basey1); glVertex2f(-1.005, 1); // au dessus à gauche
            glTexCoord2f(0.0461f, basey1); glVertex2f(1.096, 1); // au dessus à droite
            glTexCoord2f(0.0461f, basey0); glVertex2f(1.096, -1); // en bas à droite
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    if(activeMenu == 1)
        displayStartMenu();
    if(activeMenu == 2)
        displayStartMenuConfigurer();

    glutPostRedisplay();
    glutSwapBuffers(); 

}

void displayStartMenu() {
    char option1 [] = "Continuer la partie en cours";
    char option2 [] = "Commencer une nouvelle partie";
    char option3 [] = "Configurer le jeu";
    char option4 [] = "Lire les regles du jeu";
    char option5 [] = "Highscores";
    char option6 [] = "Quitter";
    char option7 [] = "Voulez-vous vraiment quitter ?";
    
    if(activeOption == 1 || activeOption == 6)
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 1, 1, 1);

    if(activeOption == 2 || activeOption == 6)
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 1, 1, 1);

    if(activeOption == 3 || activeOption == 6)
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 1, 1, 1);

    if(activeOption == 4 || activeOption == 6)
        writeOnWindow(-0.5, 0.2, option4, strlen(option4), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.2, option4, strlen(option4), 1, 1, 1);

    if(activeOption == 5 || activeOption == 6)
        writeOnWindow(-0.5, 0.1, option5, strlen(option5), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.1, option5, strlen(option5), 1, 1, 1);

    if(activeOption == 6)
        writeOnWindow(-0.5, 0.0, option7, strlen(option7), 1, 1, 1);
    else
        writeOnWindow(-0.5, 0.0, option6, strlen(option6), 1, 1, 1);
}

void displayStartMenuConfigurer() {
    char option1 [] = "Normal";
    char option2 [] = "Hardcore";
    char option3 [] = "Impossible";
    char option4 [] = "Retour";
    
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 0, 0, 0); 
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 0, 0, 0); 
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 0, 0, 0); 
        writeOnWindow(-0.5, 0.0, option4, strlen(option4), 0, 0, 0); 


    if(activeOptionMenuConfigurer == 1) {
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 2) {
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 3) {
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 4) {
        writeOnWindow(-0.5, 0.1, option4, strlen(option4), 1, 1, 1);
        return;
    }
}