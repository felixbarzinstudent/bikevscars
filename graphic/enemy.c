#include <string.h>
#include <GL/glut.h>
#include "bike.h"
#include "enemy.h"
#include "../linked-list/enemy-list.h"
#include "../linked-list/enemy-shot-list.h"
#include "../utils/calculus.h"
#include "../utils/timer-tools.h"

/* initialisation des variables */

double _timeBetweenEnemyPop = 3;
float _enemySpeedMax = 0.001; //init
float _enemySpeedMin = 0.001; //init
int _madMax = 7; // au début, 1 voiture sur 20 va suivre le vélo sur l'axe des x

/* définition des fonctions */

void followBike(Enemy* enemy);
bool isMad(int madMax);
GLuint chooseTexture(GLuint textureCar, GLuint textureAudi, GLuint textureMiniTruck, GLuint textureMiniVan, GLuint textureViper, GLuint textureTaxi);

void createEnemies(EnemyList* list, GLuint textureCar, GLuint textureAudi, GLuint textureMiniTruck, GLuint textureMiniVan, GLuint textureViper, GLuint textureTaxi) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(_timeBetweenEnemyPop)) { // crée un ennemi toutes les 'x' secondes

        Enemy* enemy = malloc(sizeof(Enemy));
        enemy->position.x = floatRandom(-0.85, 0.85);
        enemy->position.y = 1;
        enemy->position.z = 0;
        enemy->speed = floatRandom(_enemySpeedMin, _enemySpeedMax);
        enemy->isAlive = true;
        enemy->isMad = isMad(_madMax);
        enemy->textureId = chooseTexture(textureCar, textureAudi, textureMiniTruck, textureMiniVan, textureViper, textureTaxi);
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
    _madMax = 6;
}

/*
* Cette fonction permet de donner un identifiant de texture
* @Param {textureCar} texture d'une voiture rouge
* @Param {textureAudi} texture d'une audi rouge
* @Param {textureMiniTruck} texture d'un pick up
* @Param {textureMiniVan} texture d'un mini van
* @Param {textureViper} texture d'une voiture de course
* @Param {textureTaxi} texture d'un taxi
*/
GLuint chooseTexture(GLuint textureCar, GLuint textureAudi, GLuint textureMiniTruck, GLuint textureMiniVan, GLuint textureViper, GLuint textureTaxi) {
    int random = (int) floatRandom(0, 10);
    switch(random) {
        case 0 :
            return textureCar;
            break;
        case 1 :
            return textureAudi;
            break;
        case 2 :
            return textureMiniTruck;
            break;
        case 3 :
            return textureMiniVan;
            break;
        case 4 :
            return textureViper;
            break;
        case 5 :
            return textureTaxi;
            break;
        default:
            return textureTaxi;
                break;
    }
}

void drawEnemies(EnemyList* enemyList) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int enemiesCount = lengthEnemyList(enemyList);
    if(enemiesCount > 0) {
        
        if(enemyList->first != NULL) {
            glBindTexture(GL_TEXTURE_2D, enemyList->first->textureId);
            glPushMatrix();
            glLoadIdentity();

            if(enemyList->first->isAlive)
                glColor4f(1.0, 1.0, 1.0, 1);
            else {
                glColor4f(1.0, 1.0, 1.0, 0.1);
            }

            enemyList->first->position.y -= enemyList->first->speed;

            followBike(enemyList->first);

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
            glBindTexture(GL_TEXTURE_2D, current->textureId);
            glPushMatrix(); 
                if(current->isAlive)
                    glColor4f(1.0, 1.0, 1.0, 1);
                else {
                    glColor4f(1.0, 1.0, 1.0, 0.1);
                }
                current->position.y -= current->speed;
                
                followBike(current);

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

/*
* Cette fonction fait en sorte que l'ennemi suive le vélo sur l'axe des x
* @Param {enemy} l'ennemi qui suit le vélo
*/
void followBike(Enemy* enemy) {
    if (enemy->isMad && enemy->isAlive && enemy->position.y >= 0.15) {
        if(enemy->position.x > _bike.position.x) {
            enemy->position.x -= enemy->speed;
        } else if (enemy->position.x < _bike.position.x) {
            enemy->position.x += enemy->speed;
        }
    }
}

/*
* Cette fonction renvoie true si l'entier aléatoire retourné = 0;
*/
bool isMad(int max) {
    if((int)floatRandom(0, max) == 0) {
        return true;
    } 

    return false;
}