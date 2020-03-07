#include "bike.h"
#include <time.h>
#include <../GL/glut.h>
#include "./../utils/timerTools.h"
#include <math.h>
#include "./../movement/bike-movement.h"
#include "./../linked-list/shot-list.h"

/* initialisation des variables */
const int invicibilityDuration = 4;

struct Bike _bike;

void initBike() {
    _bike.position.x = 0;
    _bike.position.y = 0;
    _bike.position.z = 0;
    _bike.life = 2;
    _bike.state = 0;
    _bike.invincibilityDuration = invicibilityDuration;
}

void drawBike(){
    if(_bike.state == 1) { // 1 == invincible
        glColor4f(1.0, 0.0, 0.0, 0.1);
        if(!timerInvincibilityFunc(_bike.invincibilityDuration)) { 
            _bike.state = 0; // annule l'invincibilité
        }

    } else
        glColor4f(1.0, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.1, 0.2);
        glVertex2f(0.1, 0.2);
        glVertex2f(0.1, -0.2);
    glEnd();
    
}

bool lock = false;
time_t seconds = 0;
int lifeLoss(Bike* bike) {
    time_t secondsLater;
    secondsLater = time(NULL);
    _bike.state = 1; // invincible

    if(lock && (secondsLater - seconds) > invicibilityDuration){
        lock = false;
    }

    if (!lock) { // je bloque cette partie du code car quand on perd une vie, on devient invincible pendant un certain laps de temps
        lock = true;
        seconds = time(NULL); 
        bike->life -= 1;
        if(bike->life == 0){
            seconds = 0;
            return 1;
        }
        else 
            return 0;
    }

    return 0;
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

void shoot(List *shotList) {
    struct Shot shot;
    shot.position.x = _bike.position.x;
    shot.position.y = _bike.position.y;
    shot.position.z = 0;
    shot.speed = 0.001;
    insertFront(shotList, shot);
}