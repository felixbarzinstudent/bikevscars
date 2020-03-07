#include <GL/glut.h>
#include <math.h> 
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./navigation.h"
#include "./../graphic/bike.h"
#include "./../graphic/enemy.h"
#include "./../linked-list/shot-list.h"
#include "./../movement/bike-movement.h"
#include "./../utils/calculus.h"
#include "./../utils/textTools.h"
// #include "./../utils/timerTools.h"

/* définititon des variables*/
int numCurrentWindow;
bool isInitGame = false;
List* shotList;

/* définititon des fonctions */
void vDisplayGame();
void moveVertical();
void drawBike();
void detectCollision(Bike bike, Enemy enemy);
void detectCollisionShot(List* shotList, Enemy* enemy);
void setRandomXPosition(Enemy* enemy);
void initGame();
void keyboardownGame();
void clavierGame(unsigned char key, int x, int y);
void shoot();
void drawShots();

void windowGame() {
    initGame();
    glutDisplayFunc(vDisplayGame);
    moveVertical();
    glutSpecialFunc(keyboardownGame);
    glutKeyboardFunc(clavierGame);
}

void vDisplayGame() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    displayLife(&_bike);
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_bike.position.x, _bike.position.y, _bike.position.z);
        drawBike();
        displayBikePositionX(0, 0, _xposRecord, WIDTH, HEIGHT);
        displayCollision(-1, 0, _textCollision);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    drawShots();
    glPushMatrix();
        glTranslatef(_enemy.position.x, _enemy.position.y, _enemy.position.z);
        drawEnemy();
    glPopMatrix();
    glutPostRedisplay();
    glutSwapBuffers(); // permute buffers
}

void moveVertical() {
    if(_bike.life >= 1) { // quand le vélo n'a plus de vie, les ennemis s'arretent
        if(_enemy.position.y >= -1)
            _enemy.position.y -= 0.001;
        else {
            _enemy.position.y += 2;
            setRandomXPosition(&_enemy);
            _enemy.isAlive = true; //redonne vie a l ennemi
        }
        detectCollision(_bike, _enemy);
        detectCollisionShot(shotList, &_enemy);
    }
}

// void drawBike(){
//     if(_bike.state == 1) { // 1 == invincible
//         glColor4f(1.0, 0.0, 0.0, 0.1);
//         if(!timerInvincibilityFunc(_bike.invincibilityDuration)) { 
//             _bike.state = 0; // annule l'invincibilité
//         }

//     } else
//         glColor4f(1.0, 0.0, 0.0, 1.0);

//     glBegin(GL_POLYGON);
//         glVertex2f(-0.1, -0.2);
//         glVertex2f(-0.1, 0.2);
//         glVertex2f(0.1, 0.2);
//         glVertex2f(0.1, -0.2);
//     glEnd();
    
// }

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

void detectCollision(Bike bike, Enemy enemy) {
    if(
        enemy.isAlive == true
        &&
        (bike.position.y + 0.2 >= enemy.position.y -0.2)
        &&
        (bike.position.y - 0.2 <= enemy.position.y + 0.2)
        &&
        (bike.position.x <= (enemy.position.x + 0.2))
        &&
        (bike.position.x > (enemy.position.x - 0.2))
    ){
        strcpy(_textCollision, "Collision : true");
        int isLowLife = lifeLoss(&_bike); // TODO : make void ?
        if(isLowLife == 1) {
            setMainCurrentWindow(2);
            isInitGame = false; // pour que le jeu puisse se réinitialiser
            _bike.state = 0; // reinitialise l'etat du carré 
        }
    } else 
        strcpy(_textCollision, "Collision : false");

}

void detectCollisionShot(List* shotList, Enemy* enemy) {
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
                    if(enemy->isAlive == true)
                        delete(shotList, current); 
                 
                    enemy->isAlive = false; 
            } else if(current->position.y > 1) { 
                delete(shotList, current); // supprime de la liste chainee les tirs qui sortent de l'écran
            } 
            current = current->next;
        }

    }

}

void setRandomXPosition(Enemy* enemy) {
    enemy->position.x = floatRandom(-0.70, 0.70);
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
        initEnemy();
        isInitGame = true;
        shotList = newList();
    }
}

void keyboardownGame(int key, int x, int y) {
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

void shoot() {
    struct Shot shot;
    shot.position.x = _bike.position.x;
    shot.position.y = _bike.position.y;
    shot.position.z = 0;
    shot.speed = 0.001;
    insertFront(shotList, shot);
}

void clavierGame(unsigned char key, int x, int y) {
    if (key == 32) {
        // todo : shoot frequency (ex : pas plus de 3 tir/seconde)
        shoot();
    }
}