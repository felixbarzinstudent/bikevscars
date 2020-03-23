#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./navigation.h"
#include "./../graphic/bike.h"
#include "./../graphic/enemy.h"
#include "./../graphic/obstacle.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../records/save.h"
#include "./../utils/calculus.h"
#include "./../utils/image-loader.h"
#include "./../utils/text-tools.h"
#include "./../utils/timer-tools.h"
#include "./../structs/enemy-struct.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./../lib/stb_image.h"

/* définititon des variables*/
bool isInitGame = false;
EnemyList* enemyList;
EnemyShotList* enemyShotList;
float abasey0 = 0.0; //scrolling infini de la route
float abasey1 = 1.0; //scrolling infini de la route
float roadSpeed = 0.0003;
GLuint texture; //road
GLuint textureCar;
GLuint textureBike;
GLuint texturePolice1;
GLuint texturePolice2;
GLuint texturePolice3;
GLuint textureWave;
GLuint textureLightBeam;
GLuint textureBubble;
int previousRecordedPoints = 0;
int secondsSaved = 0;
int _totalPoints = 0;
List* shotList;

/* définititon des fonctions */
void clavierGame(unsigned char key, int x, int y);
void countPoints(int points);
void detectCollision();
void detectCollisionBike(Bike bike, Enemy* enemy);
void detectCollisionEnemiesShots(EnemyShotList* enemyShotList, Bike bike);
void detectCollisionObstacle(Bike _bike, Enemy* currentEnemy, Obstacle _obstacle);
void detectCollisionShot(List* shotList, Enemy* enemy);
void doCheckpoint();
void drawRoad();
void drawTopBoard();
void endOfGame(int isLowLife);
void initGame();
void makeItHarder();
void vDisplayGame();
void enemyShoot(Bike bike, Enemy* enemy);

void windowGame(GLuint tex) {
    texture = tex;
    initGame();
    createEnemies(enemyList);
    createObstacle();
    glutDisplayFunc(vDisplayGame);
    detectCollision();
    glutSpecialFunc(keyboardownBike);
    glutKeyboardFunc(clavierGame);
}

/*
* Cette fonction affiche la page du jeu
*/
void vDisplayGame() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawRoad();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_bike.position.x, _bike.position.y, 0);
        drawBike(textureBike);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    drawShots(textureWave, textureBubble, shotList);
    drawEnemies(textureCar, enemyList);
    drawObstacle(roadSpeed, texturePolice1, texturePolice2, texturePolice3, textureBubble);
    drawEnemiesShots(textureLightBeam, enemyShotList);
    drawTopBoard();
    glutPostRedisplay();
    glutSwapBuffers(); // permute buffers
}

/*
* Cette fonction orchestre le déplacement des ennemis depuis le dessus de l'écran vers le bas et la vérification
* des collisions
*/
void detectCollision() {
    if(_bike.life >= 1) { // quand le vélo n'a plus de vie, les ennemis s'arretent
        Enemy* currentEnemy = enemyList->first;
        while (currentEnemy != NULL) {
            if(_bike.life >= 1) { // refaire le test pour voir si le vélo est en vie au cas ou il serait mort en cour de route par un obstacle par exemple
                if (currentEnemy->position.y < -1) 
                    deleteEnemy(enemyList, currentEnemy);

                detectCollisionBike(_bike, currentEnemy); // collision entre vélo et ennemi
                enemyShoot(_bike, currentEnemy); 
                detectCollisionShot(shotList, currentEnemy); // collision entre un tir du vélo et un ennemi ou un obstacle
                detectCollisionEnemiesShots(enemyShotList, _bike); // collision entre un tir ennemi et le vélo
                detectCollisionObstacle(_bike, currentEnemy, _obstacle); // collision entre vélo, ennemi ET obstacle
            }
            currentEnemy = currentEnemy->next;
        }
    }
}

/*
* L'ennemi tire sur le vélo
*/
void enemyShoot(Bike bike, Enemy* enemy) {
    if (
        enemy->isAlive == true
        &&
        (bike.position.x <= (enemy->position.x + 0.2))
        &&
        (bike.position.x > (enemy->position.x - 0.2))
        &&
        (bike.position.y < (enemy->position.y + 0.2))
    ) {
        if (!timerEnemiesShootFunc(enemy, 1.4)) {
            if(enemy->position.x != 0 && enemy->position.y != 0) {
                printf("Position of shooting ennemy : x : %lf\n", enemy->position.x);
                printf("Position of shooting ennemy : y : %lf\n", enemy->position.y);
                shootEnemy(enemyShotList, enemy);
            }
        }
    }
}

/*
* Cette fonction permet de détecter si un vélo entre en collision avec un ennemi
* @Param {bike} vélo dont on vérifie la collision
* @Param {enemy} ennemi dont on vérifie la collision
*/
void detectCollisionBike(Bike bike, Enemy* enemy) {
    if(
        enemy->isAlive == true
        &&
        (bike.position.y + 0.2 >= enemy->position.y -0.125)
        &&
        (bike.position.y - 0.2 <= enemy->position.y + 0.2)
        &&
        (bike.position.x <= (enemy->position.x + 0.2))
        &&
        (bike.position.x > (enemy->position.x - 0.2))
    ){
        if(enemy->position.x != 0 && enemy->position.y != 0) {
            int isLowLife = lifeLoss(&_bike); // TODO : make void ?
            endOfGame(isLowLife);
        }
    } 
}

/*
* Cette fonction permet de détecter si un élément du jeu (vélo, enemi) entre en collision avec l'obstacle
*/
void detectCollisionObstacle(Bike bike, Enemy* enemy, Obstacle obstacle) {
    if(_isAlreadyObstacle && !obstacle.isBubbled) { //si il y a déja un obstacle sur la route 
        //vélo
        if(
        (bike.position.y + 0.175 >= obstacle.position.y -0.1)
        &&
        (bike.position.y - 0.2 <= obstacle.position.y + 0.1)
        &&
        (bike.position.x <= (obstacle.position.x + 0.3))
        &&
        (bike.position.x > (obstacle.position.x - 0.3))
        ){
            //printf("Le vélo est touché par un obstacle\n");
            int isLowLife = lifeLoss(&_bike);
            endOfGame(isLowLife);
        } 
        //ennemi
        if(
            (enemy->position.x > (obstacle.position.x - 0.4))
            &&
            (enemy->position.x < (obstacle.position.x + 0.4))
            &&
            (enemy->position.y < (obstacle.position.y + 0.3))
            &&
            (enemy->position.y > (obstacle.position.y - 0.3))
            ) {
                enemy->isAlive = false;
        }
    }
}

void endOfGame(int isLowLife) {
    if(isLowLife == 1) {
        setMainCurrentWindow(2);
        isInitGame = false; // pour que le jeu puisse se réinitialiser
        _bike.state = 0; // reinitialise l'etat du vélo 
        saveHighscores(_totalPoints);
    }
}

/*
* Cette fonction permet de détecter si un des tirs du vélo touche un ennemi ou un obstacle
* @Param {shotList} liste des tirs effectués par le vélo
* @Param {enemy} l'ennemi dont on vérifie s'il est touché ou non
* Pré-condition: shotList != NULL et enemy != NULL
*/
void detectCollisionShot(List* shotList, Enemy* enemy) {
    if (shotList == NULL)
        exit(EXIT_FAILURE);
    
    if (enemy == NULL)
        exit(EXIT_FAILURE);

    if (shotList->size > 0) {
        Shot* current = shotList->first;
        while(current != NULL) {
            if ( //shot VS enemy
                ((current->position.y >= enemy->position.y - 0.2) 
                &&
                (current->position.y <= enemy->position.y + 0.2)
                &&
                (current->position.x <= enemy->position.x + 0.2)
                &&
                (current->position.x > enemy->position.x - 0.2))
                ) {
                    if(current->type == _sonicWaveShot) {
                        if(enemy->isAlive == true) {
                            delete(shotList, current); 
                            countPoints(1);
                        }
                    
                        enemy->isAlive = false; 
                    }
            } else if( //shot VS obstacle
                ((current->position.x > (_obstacle.position.x - 0.4)) 
                &&
                (current->position.x < (_obstacle.position.x + 0.4))
                &&
                (current->position.y < (_obstacle.position.y + 0.15))
                &&
                (current->position.y > (_obstacle.position.y - 0.15)))
            ) {
                if(_obstacle.isBubbled && current->type == _sonicWaveShot) {
                    // max de point
                    countPoints(3);
                    _obstacle.isAlive = false;
                }
                if(!_obstacle.isBubbled && current->type == _bubbleShot) {
                    _obstacle.isBubbled = true;
                }

                delete(shotList, current); 
            } else if(current->position.y > 1) { 
                delete(shotList, current); // supprime de la liste chainee les tirs qui sortent de l'écran
            } 
            current = current->next;
        }
    }
}

/*
* Cette fonction permet de détecter si un des tirs des ennemis touche le vélo
* @Param {enemyShotList} liste des tirs effectués par les ennemis
* @Param {bike} le vélo est la cible des ennemis
*/
void detectCollisionEnemiesShots(EnemyShotList* enemyShotList, Bike bike) {
    if(bike.life >= 1) {
        if (enemyShotList == NULL)
            exit(EXIT_FAILURE);

        if (enemyShotList->size > 0) {
            Shot* current = enemyShotList->first;
            while(current != NULL) {
                if (
                    (current->position.y >= bike.position.y - 0.2)
                    &&
                    (current->position.y <= bike.position.y + 0.2)
                    &&
                    (current->position.x <= bike.position.x + 0.2)
                    &&
                    (current->position.x > bike.position.x - 0.2)
                    ) {
                        printf("Le vélo va être touché par un tir ennemi\n");
                        int isLowLife = lifeLoss(&_bike); // TODO : make void ?
                        printf("Le vélo est touché par un tir ennemi\n");
                        
                        if(isLowLife != 1)
                            deleteEnemyShot(enemyShotList, current); 

                        endOfGame(isLowLife);
                    
                } else if(current->position.y < -2) { 
                    deleteEnemyShot(enemyShotList, current); // supprime de la liste chainee les tirs qui sortent de l'écran
                } 
                current = current->next;
            }
        }
    }
}

/*
* Cette fonction orchestre le passage d'un checkpoint
*/
void doCheckpoint() {
    saveCheckpoint(_totalPoints, _bike.life, getTimeElapsed(secondsSaved));
    makeItHarder();
}

/*
* Cette fonction augmente la difficulté du jeu après chaque checkpoint
*/
void makeItHarder() {
    printf("makeitharder\n");
    _enemySpeedMax += (0.000015 * _difficulty);
    _enemySpeedMin += (0.00001 * _difficulty);
    _timeBetweenEnemyPop -= (0.35 * _difficulty);

    if(_timeBetweenEnemyPop < 0.5)
        _timeBetweenEnemyPop = 0.5;
}

/*
* Cette fonction compte les points après chaque ennemi éliminé
* Post-condition : la variable qui contient le décompte les poitns doit avoir été incrémentée
*/
void countPoints(int points) {
    _totalPoints += points;
    if(_totalPoints != 0 && _totalPoints > 10 && (_totalPoints - previousRecordedPoints) >= 10) {
        previousRecordedPoints = (_totalPoints / 10 * 10);
        doCheckpoint();
    }
}

/*
* Cette fonction est utile lors de la réinitialisation d'une partie
*/
void initGame(){
    if(!isInitGame) {
        initEnemyFactory();
        initBike();
        previousRecordedPoints = 0;
        if(_startMenuActiveOption == 1) {// reprendre depuis le dernier checkpoint (-> menu)
            _startMenuActiveOption = 0; //réinit param

            _bike.life = getLifeFromLastCheckpoint();
            _totalPoints = getPointsFromLastCheckpoint();
            secondsSaved = getTimeFromLastCheckpoint();

            previousRecordedPoints = _totalPoints;
            for (int i = 0; i < (_totalPoints / 10); i++) {
                makeItHarder();
            }
        } else {
            _totalPoints = 0;
            secondsSaved = 0;
        }

        if(_difficulty != 1) {
            makeItHarder();
        }
        _isAlreadyObstacle = false;
        shotList = newList();
        enemyList = newEnemyList();
        enemyShotList = newEnemyShotList();
        _timeTimeElapsed.lock = false;
        _timeTimeElapsed.start.tv_usec = 0;

        textureCar = loadTexture("./resources/taxialpha.png");
        textureBike = loadTexture("./resources/bike.png");
        texturePolice1 = loadTexture("./resources/police1.png");
        texturePolice2 = loadTexture("./resources/police2.png");
        texturePolice3 = loadTexture("./resources/police3.png");
        textureWave = loadTexture("./resources/wave.png");
        textureLightBeam = loadTexture("./resources/lightbeam.png");
        textureBubble = loadTexture("./resources/bubble.png");
        
        isInitGame = true;
    }
}

/*
* Cette fonction permet la gestion des touches normales appuyée sur le clavier (espace, ...)
*/
void clavierGame(unsigned char key, int x, int y) {
    switch(key) {
        case 27 : // ESC
            setMainCurrentWindow(2);
            isInitGame = false; // pour que le jeu puisse se réinitialiser
            _bike.state = 0; // reinitialise l'etat du vélo 
            break;
        case 32 : // espace
            // todo : shoot frequency (ex : pas plus de 3 tir/seconde)
            shoot(shotList, _sonicWaveShot);
            break;
        case 102 :// F
            shoot(shotList, _bubbleShot);
            break;
    }
}

void drawRoad() {
    //Clear Window
    abasey0 += roadSpeed;
    abasey1 += roadSpeed;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(-0.9539f, abasey0); glVertex2f(-1.005, -1); // en bas a gauche
        glTexCoord2f(-0.9539f, abasey1); glVertex2f(-1.005, 1); // au dessus à gauche
        glTexCoord2f(0.0461f, abasey1); glVertex2f(1.096, 1); // au dessus à droite
        glTexCoord2f(0.0461f, abasey0); glVertex2f(1.096, -1); // en bas à droite
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawTopBoard() {
    glBegin(GL_QUADS);
        glColor3f(0.4, 0.4, 0.4);
        glVertex2f(-1, 0.9);
        glVertex2f(-1, 1);
        glVertex2f(1, 1);
        glVertex2f(1, 0.9);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-1, 0.897);
        glVertex2f(-1, 0.9);
        glVertex2f(1, 0.9);
        glVertex2f(1, 0.897);
    glEnd();
    displayTopBoardText(&_bike, _totalPoints, secondsSaved);
}