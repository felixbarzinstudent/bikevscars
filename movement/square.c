/*
* Librairie contenant l'implémentation des mouvements d'un objet dans une fenêtre
*
* Import GL/glut.h pour utiliser les fonctionnalités de la librairie GLUT OpenGL
*/

#include <../GL/glut.h>
#include "square.h"
#include <string.h>
#include <stdio.h>

/* initialisation des variables */
float posX = 0, posY = 0, posZ = 0;
char xposRecord[] = "Start"; // initialise la variable qui enregistre en temps réel la position de l'objet (dans le but de l'afficher à l'écran)

void keyboardown(int key, int x, int y)
{
    float move_unit = 0.1;
    switch (key){
        case GLUT_KEY_RIGHT:
            posX+=move_unit;
            if(posX > 1.0)
                posX -= move_unit;
            char posXString[80]; 
            sprintf(posXString, "%f", posX); 
            strcpy(xposRecord, posXString);
            glFlush();
            break;

        case GLUT_KEY_LEFT:
            posX-=move_unit;;
        break;

        case GLUT_KEY_UP:
            posY+=move_unit;;
            break;

        case GLUT_KEY_DOWN:
            posY-=move_unit;;
        break;

        default:
         break;
    }
    glutPostRedisplay();
}