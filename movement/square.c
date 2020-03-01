/*
* Librairie contenant l'implémentation des mouvements d'un objet dans une fenêtre
*
* Import GL/glut.h pour utiliser les fonctionnalités de la librairie GLUT OpenGL
*/

#include <../GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "square.h"

/* initialisation des variables */
char _xposRecord[12] = "Start"; // initialise la variable qui enregistre en temps réel la position de l'objet (dans le but de l'afficher à l'écran)
struct Square _square;

void initSquare() {
    _square.position.x = 0;
    _square.position.y = 0;
    _square.position.z = 0;
    _square.life = 1;
    _square.state = 0;
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

void keyboardown(int key, int x, int y) {
    float move_unit = round(10*0.1)/10;// TODO : comment faire pour retirer l'imprécision du float ?
    move_unit-=0.000000001;
    switch (key){
        case GLUT_KEY_RIGHT:
            _square.position.x += move_unit;
            break;

        case GLUT_KEY_LEFT:
            _square.position.x -= move_unit;
            break;

        case GLUT_KEY_UP:
            _square.position.y += move_unit;
            break;

        case GLUT_KEY_DOWN:
            _square.position.y -= move_unit;
        break;

        default:
        break;
    }
    
    _square.position.x = cantGoOut(_square.position.x);
    _square.position.y = cantGoOut(_square.position.y);
    formatCoordinates(_square.position.x);

    glutPostRedisplay();
}

bool lock = false;
time_t seconds = 0;
const int invicibilityDuration = 5;
void lifeLoss(Square* square) {
    time_t secondsLater;
    secondsLater = time(NULL);

    if(lock && (secondsLater - seconds) > invicibilityDuration){
        lock = false;
    }

    if (square->life < 0){
        // TODO : end of game
        //return 2;
    } else {
        if (!lock) { // je bloque cette partie du code car quand on perd une vie, on devient invincible pendant un certain laps de temps
            lock = true;
            seconds = time(NULL); 
            square->life -= 1;
            _square.state = 1; // invincible
            //return 1;
        }

    }

    //return 0;
}