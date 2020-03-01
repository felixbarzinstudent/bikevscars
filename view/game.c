#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./../graphic/enemy.h"
#include "./../movement/square.h"
#include "./../utils/calculus.h"
#include "./../utils/textTools.h"
#include "./../utils/timerTools.h"
#include "./navigation.h"
#include <math.h> 

/* définititon des variables*/
int numCurrentWindow;
bool isInitGame = false;

/* définititon des fonctions */
void vDisplayGame();
void moveVertical();
void drawSquare();
void detectCollision(Square square, Enemy enemy);
void setRandomXPosition(Enemy* enemy);
void initGame();
void keyboardownGame();

void windowGame() {
    initGame();
    glutDisplayFunc(vDisplayGame);
    moveVertical();
    glutSpecialFunc(keyboardownGame);
}

void vDisplayGame() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    displayLife(&_square);
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_square.position.x, _square.position.y, _square.position.z);
        drawSquare();
        displaySquarePositionX(0, 0, _xposRecord, WIDTH, HEIGHT);
        displayCollision(-1, 0, _textCollision);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    glPushMatrix();
        glTranslatef(_enemy.position.x, _enemy.position.y, _enemy.position.z);
        drawEnemy();
    glPopMatrix();
    glutPostRedisplay();
    glutSwapBuffers(); // permute buffers
}

void moveVertical() {
    if(_square.life >= 1) { // quand le vélo n'a plus de vie, les ennemis s'arretent
        if(_enemy.position.y >= -1)
            _enemy.position.y -= 0.001;
        else {
            _enemy.position.y += 2;
            setRandomXPosition(&_enemy);
        }
        detectCollision(_square, _enemy);
    }
}

void drawSquare(){
    if(_square.state == 1) { // 1 == invincible
        glColor4f(1.0, 0.0, 0.0, 0.1);
        if(!timerInvincibilityFunc(_square.invincibilityDuration)) { 
            _square.state = 0; // annule l'invincibilité
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

void detectCollision(Square square, Enemy enemy) {
    if(
        (square.position.y + 0.2 >= enemy.position.y -0.2)
        &&
        (square.position.y - 0.2 <= enemy.position.y + 0.2)
        &&
        (square.position.x <= (enemy.position.x + 0.2))
        &&
        (square.position.x > (enemy.position.x - 0.2))
    ){
        strcpy(_textCollision, "Collision : true");
        int isLowLife = lifeLoss(&_square); // TODO : make void ?
        if(isLowLife == 1) {
            setMainCurrentWindow(2);
            isInitGame = false; // pour que le jeu puisse se réinitialiser
            _square.state = 0; // reinitialise l'etat du carré 
        }
    } else 
        strcpy(_textCollision, "Collision : false");

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

        initSquare();
        initEnemy();
        isInitGame = true;
    }
}

void keyboardownGame(int key, int x, int y) {
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