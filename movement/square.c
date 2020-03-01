/*
* Librairie contenant l'implémentation des mouvements d'un objet dans une fenêtre
*
* Import GL/glut.h pour utiliser les fonctionnalités de la librairie GLUT OpenGL
*/

#include <../GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "square.h"

/* initialisation des variables */
char _xposRecord[12] = "Start"; // initialise la variable qui enregistre en temps réel la position de l'objet (dans le but de l'afficher à l'écran)
struct Square _square;
const int invicibilityDuration = 4;

void initSquare() {
    _square.position.x = 0;
    _square.position.y = 0;
    _square.position.z = 0;
    _square.life = 2;
    _square.state = 0;
    _square.invincibilityDuration = invicibilityDuration;
}

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

bool lock = false;
time_t seconds = 0;
int lifeLoss(Square* square) {
    time_t secondsLater;
    secondsLater = time(NULL);
    _square.state = 1; // invincible

    if(lock && (secondsLater - seconds) > invicibilityDuration){
        lock = false;
    }

    if (!lock) { // je bloque cette partie du code car quand on perd une vie, on devient invincible pendant un certain laps de temps
        lock = true;
        seconds = time(NULL); 
        square->life -= 1;
        if(square->life == 0){
            seconds = 0;
            return 1;
        }
        else 
            return 0;
    }

    return 0;
}