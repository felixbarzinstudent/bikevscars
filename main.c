#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "movement/square.h"
#include "graphic/enemy.h"
#include "utils/calculus.h"

#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500

char text2char[10] = "";

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

void text(int x, int y, char text[])
{
    glColor3f(1,1,1);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D( 0, 600, 0, 600 );
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
             glRasterPos2i(x, y);// MET LE TEXTE EN BAS A GAUCHE 
             for ( int i = 0; i < 12; ++i )
             {
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
             }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}

void text2(int x, int y, char text[])
{glPushMatrix();
    glColor3f(1,1,1);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        //gluOrtho2D( 0, 600, 0, 600 );
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
             glRasterPos2i(x, y);// MET LE TEXTE EN BAS A GAUCHE 
             for ( int i = 0; i < 10; ++i )
             {
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
             }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
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
        strcpy(text2char, "WATCHOUT");
    } else 
        strcpy(text2char, "Ride man");

}

void setRandomXPosition(Enemy* enemy) {
    enemy->position.x = floatRandom(-0.8, 0.8);
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
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
        glTranslatef(_square.position.x, _square.position.y, _square.position.z);
        rect();
        text(0, 0, _xposRecord);
        text2(0, 0, text2char);
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