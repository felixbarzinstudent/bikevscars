#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "movement/square.h"
#include "graphic/enemy.h"
#include "utils/calculus.h"
#include "utils/textTools.h"

#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500

void reshape(int width, int heigth){ // fonction de rappel pour les redimensionnements de la fenetre

    //le parametre 'mode' (GL_PROJECTION) désigne la matrice que l'on souhaite activer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // place dans la matrice active la matrice identité (transformation nulle)

    //clip the windows so its shortest side is 2.0
    if (width < heigth) {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)heigth / (GLfloat)width, 2.0 * (GLfloat)heigth / (GLfloat)width, 2.0, 2.0);
    }
    else{
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)width / (GLfloat)heigth, 2.0 * (GLfloat)width / (GLfloat)heigth,2.0 , 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, width, heigth);
}

void rect(){
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
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
    } else 
        strcpy(_textCollision, "Collision : false");

}

void setRandomXPosition(Enemy* enemy) {
    enemy->position.x = floatRandom(-0.70, 0.70);
}

void moveVertical() {
    if(_enemy.position.y >= -1)
        _enemy.position.y -= 0.001;
    else {
        _enemy.position.y += 2;
        setRandomXPosition(&_enemy);
    }
    detectCollision(_square, _enemy);
}

void display(){
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


void init(){
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // set fill color to white
    glColor3f(1.0, 1.0, 1.0);

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
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    init();
    glutIdleFunc(moveVertical);//activation du callback
    glutSpecialFunc(keyboardown);
    glutMainLoop();

}