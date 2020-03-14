#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./navigation.h"
#include "./../graphic/bike.h"
#include "./../graphic/enemy.h"
#include "./../graphic/enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../records/save.h"
#include "./../utils/calculus.h"
#include "./../utils/text-tools.h"
#include "./../utils/timerTools.h"

/* définititon des variables*/
bool isInitGame = false;
List* shotList;
EnemyList* enemyList;
int _totalPoints = 0;

/* définititon des fonctions */
void doCheckpoint();
void vDisplayGame();
void detectCollision();
void drawBike();
void detectCollisionBike(Bike bike, Enemy* enemy);
void detectCollisionShot(List* shotList, Enemy* enemy);
void initGame();
void keyboardownBike();
void clavierGame(unsigned char key, int x, int y);
void shoot();
void drawEnemies();
void drawShots();
void countPoints();
void makeItHarder();

void windowGame() {
    initGame();
    createEnemies(enemyList);
    glutDisplayFunc(vDisplayGame);
    detectCollision();
    glutSpecialFunc(keyboardownBike);
    glutKeyboardFunc(clavierGame);
}

void vDisplayGame() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    displayLife(&_bike);
    displayScore(_totalPoints);
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_bike.position.x, _bike.position.y, _bike.position.z);
        drawBike();
        displayBikePositionX(0, 0, _xposRecord, WIDTH, HEIGHT);
        displayCollision(-1, 0, _textCollision);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    drawShots();
    drawEnemies();
    glutPostRedisplay();
    glutSwapBuffers(); // permute buffers
}

void detectCollision() {
    if(_bike.life >= 1) { // quand le vélo n'a plus de vie, les ennemis s'arretent
        Enemy* currentEnemy = enemyList->first;
        while (currentEnemy != NULL) {
            if (currentEnemy->position.y < -2) 
                deleteEnemy(enemyList, currentEnemy);

            detectCollisionBike(_bike, currentEnemy);
            detectCollisionShot(shotList, currentEnemy);
            currentEnemy = currentEnemy->next;
        }
    }
}

void drawEnemies() {
    glColor3f(0.0, 1.0, 0.0);
    int enemiesCount = lengthEnemyList(enemyList);
    if(enemiesCount > 0) {
        
        if(enemyList->first != NULL) {
            if(enemyList->first->isAlive == true)
                glColor3f(0.0, 1.0, 0.0);
            else
                glColor4f(0.0, 1.0, 0.0, 0.1);
            glPushMatrix();
            enemyList->first->position.y -= enemyList->first->speed;
            glTranslatef(enemyList->first->position.x, enemyList->first->position.y, enemyList->first->position.z);
            glBegin(GL_POLYGON);
                glVertex2f(-0.1, -0.2);
                glVertex2f(-0.1, 0.2);
                glVertex2f(0.1, 0.2);
                glVertex2f(0.1, -0.2);
            glEnd();
            glPopMatrix();
        } else {
            exit(EXIT_FAILURE);
        }

        if(enemiesCount > 1) {
            Enemy* current = enemyList->first->next;
            while(current != NULL) {
                if(current->isAlive == true)
                    glColor3f(0.0, 1.0, 0.0);
                else
                    glColor4f(0.0, 1.0, 0.0, 0.1);
                glPushMatrix(); 
                current->position.y -= current->speed;
                glTranslatef(current->position.x, current->position.y, current->position.z);
                glBegin(GL_POLYGON);
                    glVertex2f(-0.1, -0.2);
                    glVertex2f(-0.1, 0.2);
                    glVertex2f(0.1, 0.2);
                    glVertex2f(0.1, -0.2);
                glEnd();
                glPopMatrix(); 
                current = current->next;
            }

        }
    }
}

void drawShots() {
    glColor4f(1.0, 1.0, 1.0, 0.1);
    int shotsCount = length(shotList);
    if(shotsCount > 0) {
        
        if(shotList->first != NULL) {
            glPushMatrix();
            shotList->first->position.y += shotList->first->speed;
            glTranslatef(shotList->first->position.x, shotList->first->position.y, shotList->first->position.z);
            glBegin(GL_POLYGON);
                glVertex2f(-0.05, -0.1);
                glVertex2f(-0.05, 0.1);
                glVertex2f(0.05, 0.1);
                glVertex2f(0.05, -0.1);
            glEnd();
            glPopMatrix();
        } else {
            exit(EXIT_FAILURE);
        }

        if(shotsCount > 1) {
            Shot* current = shotList->first->next;
            while(current != NULL) {
                glPushMatrix(); 
                current->position.y += current->speed;
                glTranslatef(current->position.x, current->position.y, current->position.z);
                glBegin(GL_POLYGON);
                    glVertex2f(-0.05, -0.1);
                    glVertex2f(-0.05, 0.1);
                    glVertex2f(0.05, 0.1);
                    glVertex2f(0.05, -0.1);
                glEnd();
                glPopMatrix(); 
                current = current->next;
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
        (bike.position.y + 0.2 >= enemy->position.y -0.2)
        &&
        (bike.position.y - 0.2 <= enemy->position.y + 0.2)
        &&
        (bike.position.x <= (enemy->position.x + 0.2))
        &&
        (bike.position.x > (enemy->position.x - 0.2))
    ){
        strcpy(_textCollision, "Collision : true");
        int isLowLife = lifeLoss(&_bike); // TODO : make void ?
        if(isLowLife == 1) {
            setMainCurrentWindow(2);
            isInitGame = false; // pour que le jeu puisse se réinitialiser
            _bike.state = 0; // reinitialise l'etat du vélo 
            saveHighscores(_totalPoints);
        }
    } else 
        strcpy(_textCollision, "Collision : false");

}

/*
* Cette fonction permet de détecter si un des tirs du vélo touche un ennemi
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
            if (
                (current->position.y >= enemy->position.y - 0.2)
                &&
                (current->position.y <= enemy->position.y + 0.2)
                &&
                (current->position.x <= enemy->position.x + 0.2)
                &&
                (current->position.x > enemy->position.x - 0.2)
                ) {
                    if(enemy->isAlive == true) {
                        delete(shotList, current); 
                        countPoints();
                    }
                 
                    enemy->isAlive = false; 
            } else if(current->position.y > 1) { 
                delete(shotList, current); // supprime de la liste chainee les tirs qui sortent de l'écran
            } 
            current = current->next;
        }
    }
}

void doCheckpoint() {
    saveCheckpoint(_totalPoints, _bike.life);
    makeItHarder();
}

/*
* Cette fonction augmente la difficulté du jeu après chaque checkpoint
*/
void makeItHarder() {
    printf("makeitharder\n");
    enemySpeedMax += 0.000015;
    enemySpeedMin += 0.00001;
    timeBetweenEnemyPop -= 0.35;

    if(timeBetweenEnemyPop < 0.5)
        timeBetweenEnemyPop = 0.5;
}

void countPoints() {
    _totalPoints++;
    if(_totalPoints != 0 && _totalPoints % 10 == 0) {
        doCheckpoint();
    }
}

void initGame(){
    if(!isInitGame) {
        // set clear color to black
        glClearColor(0.0, 0.0, 0.0, 0.0);

        // set fill color to white
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //set up standard orthogonal view with clipping
        //box as cube of side 2 centered at origin
        //This is the default view and these statements could be removed
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        initBike();
        isInitGame = true;
        _totalPoints = 0;
        shotList = newList();
        enemyList = newEnemyList();
    }
}

void clavierGame(unsigned char key, int x, int y) {
    if (key == 32) {
        // todo : shoot frequency (ex : pas plus de 3 tir/seconde)
        shoot(shotList);
    }
}