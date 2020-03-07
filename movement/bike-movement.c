/*
* Librairie contenant l'implémentation des mouvements d'un objet dans une fenêtre
*
* Import GL/glut.h pour utiliser les fonctionnalités de la librairie GLUT OpenGL
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bike-movement.h"
#include <../GL/glut.h>
#include <math.h>
#include "./../graphic/bike.h"

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

void keyboardownBike(int key, int x, int y) {
    float move_unit = round(10*0.1)/10;// TODO : comment faire pour retirer l'imprécision du float ?
    move_unit-=0.000000001;
    switch (key){
        case GLUT_KEY_RIGHT:
            _bike.position.x += move_unit;
            break;

        case GLUT_KEY_LEFT:
            _bike.position.x -= move_unit;
            break;

        case GLUT_KEY_UP:
            _bike.position.y += move_unit;
            break;

        case GLUT_KEY_DOWN:
            _bike.position.y -= move_unit;
        break;

        default:
        break;
    }
    
    _bike.position.x = cantGoOut(_bike.position.x);
    _bike.position.y = cantGoOut(_bike.position.y);
    formatCoordinates(_bike.position.x);

    glutPostRedisplay();
}