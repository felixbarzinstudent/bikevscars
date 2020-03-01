#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./game.h"
#include "./navigation.h"
#include "./../graphic/enemy.h"
#include "./../movement/square.h"
#include "./../utils/calculus.h"
#include "./../utils/textTools.h"
#include "./../utils/timerTools.h"

/* définititon des variables*/
int numCurrentWindow;
int windowEndGame_endGame;

/* définititon des fonctions */
void vClavier(unsigned char key, int x, int y);
void vClavierSpecial(int key, int x, int y);
void vDisplay();
void vReshape();
void moveVertical();
void drawSquare();
void detectCollision(Square square, Enemy enemy);
void setRandomXPosition(Enemy* enemy);
void init();

void windowGame(int numWindows[]) {
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(XWINDOWPOSITION, YWINDOWPOSITION);
    numWindows[1] = glutCreateWindow("Bike VS Cars");
    numCurrentWindow = numWindows[1];
    windowEndGame_endGame = numWindows[2];
    glutDisplayFunc(vDisplay);
    init();
    glutIdleFunc(moveVertical);//activation du callback
    glutSpecialFunc(keyboardown);
}

void vClavierSpecial(int key, int x, int y) 
{
	switch (key){
        case GLUT_KEY_UP:
        // TODO : change current selected window
            break;

        case GLUT_KEY_DOWN:
        break;

        default:
        break;
    }
}

void vClavier(unsigned char key, int x, int y) {
    
}

void vDisplay() {
    //if(glutGetWindow() == getCurrentMainWindow()) {
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
    //}
}

void vReshape() {
    //le parametre 'mode' (GL_PROJECTION) désigne la matrice que l'on souhaite activer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // place dans la matrice active la matrice identité (transformation nulle)

    //clip the windows so its shortest side is 2.0
    if (WIDTH < HEIGHT) {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)HEIGHT / (GLfloat)WIDTH, 2.0 * (GLfloat)HEIGHT / (GLfloat)WIDTH, 2.0, 2.0);
    }
    else {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)WIDTH / (GLfloat)HEIGHT, 2.0 * (GLfloat)WIDTH / (GLfloat)HEIGHT,2.0 , 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, WIDTH, HEIGHT);
}

void moveVertical() {
    if(glutGetWindow() == getCurrentMainWindow()) {
        //glutShowWindow();
        if(_square.life > 0) { // quand le vélo n'a plus de vie, les ennemis s'arretent
            if(_enemy.position.y >= -1)
                _enemy.position.y -= 0.001;
            else {
                _enemy.position.y += 2;
                setRandomXPosition(&_enemy);
            }
            detectCollision(_square, _enemy);
        }

    }
}

void drawSquare(){
    if(_square.state == 1) { // 1 == invincible
        glColor4f(1.0, 0.0, 0.0, 0.1);
        if(!timerInvincibilityFunc(5)) { 
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
        int isEndOfGame = lifeLoss(&_square);
        if (isEndOfGame == 1) {
            glutHideWindow();
            glutSetWindow(windowEndGame_endGame); //ouvre la fenêtre de fin de jeu
            setCurrentMainWindow(windowEndGame_endGame);
            glutShowWindow();
            //glutDestroyWindow(glutGetWindow());
        }
    } else 
        strcpy(_textCollision, "Collision : false");

}

void setRandomXPosition(Enemy* enemy) {
    enemy->position.x = floatRandom(-0.70, 0.70);
}

void init(){
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // set fill color to white
    //glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //set up standard orthogonal view with clipping
    //box as cube of side 2 centered at origin
    //This is the default view and these statements could be removed
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-1.0, 1.0, -1.0, 1.0);// parametre de camera (+-)
    glutHideWindow();
    initSquare();
    initEnemy();
}