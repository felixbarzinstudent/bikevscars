#include <time.h>
#include <../GL/glut.h>
#include "./bike.h"
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../utils/timer-tools.h"

/* initialisation des variables */
const double bikeCooldown = 0.75; // temps de pause entre les tirs
const double bikeStartPosition = -0.75;
const double invicibilityDuration = 4; // temps pendant lequel le vélo est invincible apres avoir perdu une vie
const float initialShotSpeed = 0.00176;
const int _sonicWaveShot = 1;
const int _bubbleShot = 2;
const int bikeStateVulnerable = 0;
const int bikeStateInvincible = 1;
const int maxRafaleShoot = 3; // nombre de tir max que peut contenir une rafale de tire du vélo
int counterShoot = 0; // pour compter le nombre de tirs avant déclenchement du cooldown
struct Bike _bike;

/* définition des fonctions */

void initBike() {
    _bike.position.x = 0;
    _bike.position.y = bikeStartPosition;
    _bike.position.z = 0;
    _bike.life = 3;
    _bike.state = bikeStateVulnerable;
    _bike.invincibilityDuration = invicibilityDuration;
}

void drawBike(GLuint texture){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        if(_bike.state == 1) { // 1 == invincible
            glColor4f(1.0, 1.0, 0.1, 0.1);
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
    _bike.state = bikeStateInvincible;

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

void shoot(List *shotList, int type) {

    if (shotList == NULL)
        exit(EXIT_FAILURE);

    if(counterShoot < maxRafaleShoot) {
        counterShoot ++;
        Shot* shot = malloc(sizeof(Shot));
        shot->position.x = _bike.position.x;
        shot->position.y = (_bike.position.y + 0.2);
        shot->position.z = 0;
        shot->speed = initialShotSpeed;
        shot->type = type;
        insertFront(shotList, shot);
        if(!timerBikeCooldownFunc(bikeCooldown)) { // si le vélo ne spam pas ses tirs, pas besoin de cooldown
            counterShoot = 0;
        }
    } 
    if(counterShoot >= maxRafaleShoot) { // si le vélo spam ses tirs -> cooldown
        if(!timerBikeCooldownFunc(bikeCooldown)) {
            counterShoot = 0;
        }
    }
}

void drawShots(GLuint textureWave, GLuint textureBubble, List *shotList) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    
    int shotsCount = length(shotList);
    if(shotsCount > 0) {
        
        if(shotList->first != NULL) {
            glPushMatrix();
                if(shotList->first->type == _sonicWaveShot) {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, textureWave);
                    glColor4f(0.5, 0.4, 0.4, 0.5);
                    shotList->first->position.y += shotList->first->speed;
                    glTranslatef(shotList->first->position.x, shotList->first->position.y, 0);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 1); glVertex2f(-0.05, -0.1); //en bas a gauche
                        glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1); // au dessus a gauche
                        glTexCoord2f(1, 0); glVertex2f(0.05, 0.1); // au dessus a droite
                        glTexCoord2f(1, 1); glVertex2f(0.05, -0.1); // en bas a droite
                    glEnd();
                } else if (shotList->first->type == _bubbleShot) {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
                    glColor3f(1, 1, 1);
                    glBindTexture(GL_TEXTURE_2D, textureBubble);
                    shotList->first->position.y += (shotList->first->speed / 2); // une bulle de savon va deux fois moins vite
                    glTranslatef(shotList->first->position.x, shotList->first->position.y, 0);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 1); glVertex2f(-0.05, -0.015); //en bas a gauche
                        glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1); // au dessus a gauche
                        glTexCoord2f(1, 0); glVertex2f(0.05, 0.1); // au dessus a droite
                        glTexCoord2f(1, 1); glVertex2f(0.05, -0.015); // en bas a droite
                    glEnd();
                }
            glPopMatrix();
        } else {
            exit(EXIT_FAILURE);
        }

        if(shotsCount > 1) {
            Shot* current = shotList->first->next;
            while(current != NULL) {
                glPushMatrix(); 
                    if(current->type == _sonicWaveShot) {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        glColor4f(0.5, 0.4, 0.4, 0.5);
                        glBindTexture(GL_TEXTURE_2D, textureWave);
                        current->position.y += current->speed;
                        glTranslatef(current->position.x, current->position.y, 0);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0, 1); glVertex2f(-0.05, -0.1);
                            glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1);
                            glTexCoord2f(1, 0); glVertex2f(0.05, 0.1);
                            glTexCoord2f(1, 1); glVertex2f(0.05, -0.1);
                        glEnd();
                    } else if (current->type == _bubbleShot) {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
                        glColor4f(1, 1, 1, 1);
                        glBindTexture(GL_TEXTURE_2D, textureBubble);
                        current->position.y += (current->speed / 2); // une bulle de savon va deux fois moins vite
                        glTranslatef(current->position.x, current->position.y, 0);
                        glBegin(GL_QUADS);
                            glTexCoord2f(0, 1); glVertex2f(-0.05, -0.015); //en bas a gauche
                            glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1); // au dessus a gauche
                            glTexCoord2f(1, 0); glVertex2f(0.05, 0.1); // au dessus a droite
                            glTexCoord2f(1, 1); glVertex2f(0.05, -0.015); // en bas a droite
                        glEnd();
                    }
                    
                glPopMatrix(); 
                current = current->next;
            }
        }
    }
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}