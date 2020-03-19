#include "bike.h"
#include <time.h>
#include <../GL/glut.h>
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
const double invicibilityDuration = 4;

struct Bike _bike;

//TODO : utiliser un enum pour le state
void initBike() {
    _bike.position.x = 0;
    _bike.position.y = 0;
    _bike.position.z = 0;
    _bike.life = 2;
    _bike.state = 0; // 0 == vulnérable et 1 == invincible
    _bike.invincibilityDuration = invicibilityDuration;
}

void drawBike(GLuint texture){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
    if(_bike.state == 1) { // 1 == invincible
        //glColor4f(1.0, 0.0, 0.0, 0.1);
        if(!timerInvincibilityFunc(_bike.invincibilityDuration)) { 
            _bike.state = 0; // annule l'invincibilité
        }

    } else
        glColor4f(1.0, 1.0, 0.1, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-0.1, -0.2);//en bas a gauche
        glTexCoord2f(0, 0); glVertex2f(-0.1, 0.2);// au dessus a gauche
        glTexCoord2f(1, 0); glVertex2f(0.1, 0.2);//au dessus à droite
        glTexCoord2f(1, 1); glVertex2f(0.1, -0.2);//en bas a droite
    glEnd();
    
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

bool lock = false;
time_t seconds = 0;
int lifeLoss(Bike* bike) {
    if(bike == NULL)
        exit(EXIT_FAILURE);
    if(bike->life <= 0)
        exit(EXIT_FAILURE);

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

void shoot(List *shotList) {

    if (shotList == NULL)
        exit(EXIT_FAILURE);

    Shot shot;
    shot.position.x = _bike.position.x;
    shot.position.y = _bike.position.y;
    shot.position.z = 0;
    shot.speed = 0.001;
    insertFront(shotList, shot);
}