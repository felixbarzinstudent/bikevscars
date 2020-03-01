#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "movement/square.h"
#include "graphic/enemy.h"
#include "utils/calculus.h"
#include "utils/textTools.h"
#include "utils/timerTools.h"
#include "view/start-menu.h"

/* définition des variables */
#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500

/*
* définition des variables globales
* variables globales relatives aux numéros des fenêtres du programme
* Ces propriétés sont settées au moment ou la fenêtre est crée, il ne faut en aucun cas les 
* modifier ensuite
* 0 = fenetre menu départ
* 1 = fenetre de jeux
*/
int numWindows[2];

void reshape(int width, int heigth){ // fonction de rappel pour les redimensionnements de la fenetre

    //le parametre 'mode' (GL_PROJECTION) désigne la matrice que l'on souhaite activer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // place dans la matrice active la matrice identité (transformation nulle)

    //clip the windows so its shortest side is 2.0
    if (width < heigth) {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)heigth / (GLfloat)width, 2.0 * (GLfloat)heigth / (GLfloat)width, 2.0, 2.0);
    }
    else {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)width / (GLfloat)heigth, 2.0 * (GLfloat)width / (GLfloat)heigth,2.0 , 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, width, heigth);
}

void rect(){
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
        lifeLoss(&_square); // TODO : make void ?
    } else 
        strcpy(_textCollision, "Collision : false");

}

void setRandomXPosition(Enemy* enemy) {
    enemy->position.x = floatRandom(-0.70, 0.70);
}

void moveVertical() {
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

// UNUSED
void drawMenu() {
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-1.0, -0.5);
        glVertex2f(1.0, -0.5);
        glVertex2f(1.0, -1.0);
    glEnd();
}

void display(){
    if(glutGetWindow() == numWindows[1]) { // si la fenetre courante (ouverte) est celle du jeu, alors le jeu peu être activé
        //Clear Window
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
        displayLife(&_square);
        glLoadIdentity();
        glPushMatrix();// sauvegarde l'état actuel de la matrice
            glTranslatef(_square.position.x, _square.position.y, _square.position.z);
            rect();
            displaySquarePositionX(0, 0, _xposRecord, WINDOWWIDTH, WINDOWHEIGHT);
            displayCollision(-1, 0, _textCollision);
        glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
        glPushMatrix();
            glTranslatef(_enemy.position.x, _enemy.position.y, _enemy.position.z);
            drawEnemy();
        glPopMatrix();
        glutPostRedisplay();
        glutSwapBuffers(); // permute buffers
    }

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

    initSquare();
    initEnemy();
}

int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    //Windows tittle is name of program

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //GLUT_DOUBLE pour activer le double buffering et GLUT_RGBA pour activer le mode couleur 32 bits
    
    glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
    glutInitWindowPosition(0, 0);
    numWindows[1] = glutCreateWindow("Bike VS Cars");
    glutDisplayFunc(display);
    init();
    glutIdleFunc(moveVertical);//activation du callback
    glutSpecialFunc(keyboardown);

    /* fenêtre du menu de départ */
    windowMenu(numWindows);

    glutMainLoop();

}