#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./navigation.h"
#include "./../graphic/bike.h"
#include "./../graphic/enemy.h"
#include "./../graphic/enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../records/save.h"
#include "./../utils/calculus.h"
#include "./../utils/text-tools.h"
#include "./../utils/timerTools.h"
#include "./../structs/enemy-struct.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./../lib/stb_image.h"


/* définititon des variables*/
bool isInitGame = false;
List* shotList;
EnemyList* enemyList;
EnemyShotList* enemyShotList;
int _totalPoints = 0;
GLuint textureCar;

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
void drawEnemiesShots();
void countPoints();
void makeItHarder();
void enemyShoot(Bike bike, Enemy* enemy);
void detectCollisionEnemiesShots(EnemyShotList* enemyShotList, Bike bike);
void endOfGame(int isLowLife);

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
    //displayLife(&_bike);
    //displayScore(_totalPoints);
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_bike.position.x, _bike.position.y, _bike.position.z);
        drawBike();
        //displayBikePositionX(0, 0, _xposRecord, WIDTH, HEIGHT);
        //displayCollision(-1, 0, _textCollision);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    drawShots();
    drawEnemies();
    drawEnemiesShots();
    glutPostRedisplay();
    glutSwapBuffers(); // permute buffers
}

void detectCollision() {
    if(_bike.life >= 1) { // quand le vélo n'a plus de vie, les ennemis s'arretent
        Enemy* currentEnemy = enemyList->first;
        while (currentEnemy != NULL) {
            if (currentEnemy->position.y < -1) 
                deleteEnemy(enemyList, currentEnemy);

            detectCollisionBike(_bike, currentEnemy);
            enemyShoot(_bike, currentEnemy);
            detectCollisionShot(shotList, currentEnemy);
            detectCollisionEnemiesShots(enemyShotList, _bike);
            currentEnemy = currentEnemy->next;
        }
    }
}

void drawEnemies() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCar);

    int enemiesCount = lengthEnemyList(enemyList);
    if(enemiesCount > 0) {
        
        if(enemyList->first != NULL) {
            glPushMatrix();
            glLoadIdentity();
                enemyList->first->position.y -= enemyList->first->speed;
                glTranslatef(enemyList->first->position.x, enemyList->first->position.y, enemyList->first->position.z);
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 0); glVertex2f(-0.1, -0.2);
                    glTexCoord2f(1, 1); glVertex2f(-0.1, 0.2);
                    glTexCoord2f(0, 1); glVertex2f(0.1, 0.2);
                    glTexCoord2f(0, 0); glVertex2f(0.1, -0.2);
                glEnd();
            glPopMatrix();
        } else {
            printf("exit failure ?\n");
        }
        if(enemiesCount > 1) {
            Enemy* current = enemyList->first->next;
            while(current != NULL) {
            glPushMatrix(); 
                current->position.y -= current->speed;
                glTranslatef(current->position.x, current->position.y, current->position.z);
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 0); glVertex2f(-0.1, -0.2);
                    glTexCoord2f(1, 1); glVertex2f(-0.1, 0.2);
                    glTexCoord2f(0, 1); glVertex2f(0.1, 0.2);
                    glTexCoord2f(0, 0); glVertex2f(0.1, -0.2);
                glEnd();
            glPopMatrix(); 
                current = current->next;
            }

        }
    }
    glDisable(GL_TEXTURE_2D);
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

void drawEnemiesShots() {
    glColor4f(1.0, 1.0, 1.0, 0.1);
    int shotsCount = lengthEnemyShotList(enemyShotList);
    if(shotsCount > 0) {
        
        if(enemyShotList->first != NULL) {
            glPushMatrix();
                enemyShotList->first->position.y -= enemyShotList->first->speed;
                glTranslatef(enemyShotList->first->position.x, enemyShotList->first->position.y, enemyShotList->first->position.z);
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
            Shot* current = enemyShotList->first->next;
            while(current != NULL) {
                glPushMatrix(); 
                    current->position.y -= current->speed;
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

void enemyShoot(Bike bike, Enemy* enemy) {
    if (
        enemy->isAlive == true
        &&
        (bike.position.x <= (enemy->position.x + 0.2))
        &&
        (bike.position.x > (enemy->position.x - 0.2))
    ) {
        if (!timerEnemiesShootFunc(enemy, 1.75)) {
            shootEnemy(enemyShotList, enemy);
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
        endOfGame(isLowLife);
    } else 
        strcpy(_textCollision, "Collision : false");

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

void detectCollisionEnemiesShots(EnemyShotList* enemyShotList, Bike bike) {
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
                    deleteEnemyShot(enemyShotList, current); 
                    int isLowLife = lifeLoss(&_bike); // TODO : make void ?
                    endOfGame(isLowLife);
                 
            } else if(current->position.y < -1) { 
                deleteEnemyShot(enemyShotList, current); // supprime de la liste chainee les tirs qui sortent de l'écran
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
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0.0, 0.0, 0.0, 0.0);

        // set fill color to white
        glEnable(GL_BLEND);
        glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        glClearColor(0.0,0.0,0.0,0.0);
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
        enemyShotList = newEnemyShotList();



        //TODO : mettre ca dans un fichier a part
        int x, y, n;
        unsigned char *data = stbi_load("./resources/taxialpha.png", &x, &y, &n, 4);
        GLuint glId;
        glGenTextures(1, &glId);
        glBindTexture(GL_TEXTURE_2D, glId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // (Actually, this one is the default)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        textureCar = glId;
    }
}

void clavierGame(unsigned char key, int x, int y) {
    if (key == 32) {
        // todo : shoot frequency (ex : pas plus de 3 tir/seconde)
        shoot(shotList);
    }
}