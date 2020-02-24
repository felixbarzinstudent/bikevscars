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
float posX = 0, posY = 0;
const float posZ = 0; // l'axe Z ne sera pas utilisée donc on peut utiliser une constante == 0
char xposRecord[] = "Start"; // initialise la variable qui enregistre en temps réel la position de l'objet (dans le but de l'afficher à l'écran)

void formatCoordinates(float coordinate) {
    char posXString[80]; 
    sprintf(posXString, "%f", coordinate); 
    strcpy(xposRecord, posXString);
}

float cantGoOut(float coordinate) {
    if(coordinate >= 0)
        return coordinate <= 1.0f ? coordinate : 1.0f;
    else 
        return coordinate >= -1.0f ? coordinate : -1.0f;
}

void keyboardown(int key, int x, int y)
{
    float move_unit = 0.1;
    switch (key){
        case GLUT_KEY_RIGHT:
            posX += move_unit;
            break;

        case GLUT_KEY_LEFT:
            posX -= move_unit;;
            break;

        case GLUT_KEY_UP:
            posY += move_unit;;
            break;

        case GLUT_KEY_DOWN:
            posY -= move_unit;;
        break;

        default:
        break;
    }
    
    posX = cantGoOut(posX);
    posY = cantGoOut(posY);
    formatCoordinates(posX);

    glutPostRedisplay();
}