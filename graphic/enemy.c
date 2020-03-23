#include <string.h>
#include <../GL/glut.h>
#include "./enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timer-tools.h"

/* initialisation des variables */

double _timeBetweenEnemyPop = 3;
float _enemySpeedMax = 0.001; //init
float _enemySpeedMin = 0.001; //init

/* définition des fonctions */

void createEnemies(EnemyList* list) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(_timeBetweenEnemyPop)) { // crée un ennemi toutes les 'x' secondes
        Enemy* enemy = malloc(sizeof(Enemy));
        enemy->position.x = floatRandom(-0.85, 0.85);
        enemy->position.y = 1;
        enemy->position.z = 0;
        enemy->speed = floatRandom(_enemySpeedMin, _enemySpeedMax);
        enemy->isAlive = true;
        insertEnemyFront(list, enemy);
    }
}

void shootEnemy (EnemyShotList* enemyShotList, Enemy* enemy) {
    if (enemyShotList == NULL)
        exit(EXIT_FAILURE);

    Shot* shot = malloc(sizeof(Shot));
    shot->position.x = enemy->position.x;
    shot->position.y = (enemy->position.y - 0.2);
    shot->position.z = 0;
    shot->speed = (_enemySpeedMin + 0.001);
    insertEnemyShotFront(enemyShotList, shot);
}

void initEnemyFactory() {
    _enemySpeedMax = 0.001;
    _enemySpeedMin = 0.001;
    _timeBetweenEnemyPop = 3;
}

void drawEnemies(GLuint textureCar, EnemyList* enemyList) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureCar);

    int enemiesCount = lengthEnemyList(enemyList);
    if(enemiesCount > 0) {
        
        if(enemyList->first != NULL) {
            glPushMatrix();
            glLoadIdentity();

            if(enemyList->first->isAlive)
                glColor4f(1.0, 1.0, 0.1, 1);
            else {
                glColor4f(1.0, 1.0, 0.1, 0.1);
            }

                enemyList->first->position.y -= enemyList->first->speed;
                glTranslatef(enemyList->first->position.x, enemyList->first->position.y, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(-0.1, -0.2);//en bas a gauche
                    glTexCoord2f(0, 0); glVertex2f(-0.1, 0.2);// au dessus a gauche
                    glTexCoord2f(1, 0); glVertex2f(0.1, 0.2);//au dessus à droite
                    glTexCoord2f(1, 1); glVertex2f(0.1, -0.2);//en bas a droite
                glEnd();
            glPopMatrix();
        } 
        
        if(enemiesCount > 1) {
            Enemy* current = enemyList->first->next;
            while(current != NULL) {
            glPushMatrix(); 
                if(current->isAlive)
                    glColor4f(1.0, 1.0, 0.1, 1);
                else {
                    glColor4f(1.0, 1.0, 0.1, 0.1);
                }
                current->position.y -= current->speed;
                glTranslatef(current->position.x, current->position.y, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(-0.1, -0.2);//en bas a gauche
                    glTexCoord2f(0, 0); glVertex2f(-0.1, 0.2);// au dessus a gauche
                    glTexCoord2f(1, 0); glVertex2f(0.1, 0.2);//au dessus à droite
                    glTexCoord2f(1, 1); glVertex2f(0.1, -0.2);//en bas a droite
                glEnd();
            glPopMatrix(); 
                current = current->next;
            }

        }
    }
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void drawEnemiesShots(GLuint textureLightBeam, EnemyShotList* enemyShotList) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureLightBeam);

    glColor4f(1.0, 1.0, 1.0, 1);
    int shotsCount = lengthEnemyShotList(enemyShotList);
    if(shotsCount > 0) {
        
        if(enemyShotList->first != NULL) {
            glPushMatrix();
                enemyShotList->first->position.y -= enemyShotList->first->speed;
                glTranslatef(enemyShotList->first->position.x, enemyShotList->first->position.y, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 1); glVertex2f(-0.05, -0.1);
                    glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1);
                    glTexCoord2f(1, 0); glVertex2f(0.05, 0.1);
                    glTexCoord2f(1, 1); glVertex2f(0.05, -0.1);
                glEnd();
            glPopMatrix();
        } else {
            exit(EXIT_FAILURE);
        }

        if(shotsCount > 1) {
            Shot* current = enemyShotList->first->next;
            while(current != NULL) {
                glPushMatrix(); 
                    current->position.y -= current->speed;
                    glTranslatef(current->position.x, current->position.y, 0);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 1); glVertex2f(-0.05, -0.1);
                        glTexCoord2f(0, 0); glVertex2f(-0.05, 0.1);
                        glTexCoord2f(1, 0); glVertex2f(0.05, 0.1);
                        glTexCoord2f(1, 1); glVertex2f(0.05, -0.1);
                    glEnd();
                glPopMatrix(); 
                current = current->next;
            }

        }
    }
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}