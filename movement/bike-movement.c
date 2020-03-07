/*
* Librairie contenant l'implémentation des mouvements d'un objet dans une fenêtre
*
* Import GL/glut.h pour utiliser les fonctionnalités de la librairie GLUT OpenGL
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bike-movement.h"

// /* initialisation des variables */
char _xposRecord[12] = "Start"; // initialise la variable qui enregistre en temps réel la position de l'objet (dans le but de l'afficher à l'écran)

void formatCoordinates(float coordinate) {
    char posXString[12]; 
    sprintf(posXString, "%.9f", coordinate); 
    strcpy(_xposRecord, posXString);
}

float cantGoOut(float coordinate) {
    if(coordinate >= 0)
        return coordinate <= 1.0f ? coordinate : 1.0f;
    else 
        return coordinate >= -1.0f ? coordinate : -1.0f;
}