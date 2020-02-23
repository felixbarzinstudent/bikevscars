#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "movement/square.h"

GLfloat rotation = 90.0;
float posX, posY, posZ;
char xposFollow[] = "Start";
void reshape(int width, int heigth){ // fonction de rappel pour les redimensionnements de la fenetre
    /* window reshape when made it bigger or smaller*/

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

void text(char xposFollow[])
{
    char menu[80];
    strcpy(menu,xposFollow);
    int len;
    len = strlen(menu);

    glColor3f(1,1,1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D( 0, 600, 0, 600 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    glLoadIdentity();

    glRasterPos2i(0, 0);// MET LE TEXTE EN BAS A GAUCHE 


    for ( int i = 0; i < len; ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
    }

    glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}

void display(){
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // le mode GL_MODELVIEW permet de faire des transformations sur les objets de la scène
    glLoadIdentity();
    glPushMatrix();// sauvegarde l'état actuel de la matrice
    glTranslatef(posX,posY,posZ);
    rect();
    text(xposFollow);
    glPopMatrix();// la matrice revient à l'état ou elle était au dernier glPushMatrix()
    glFlush();
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

}
// void keyboardown(int key, int x, int y)
// {
//     float move_unit = 0.1;
//     switch (key){
//         case GLUT_KEY_RIGHT:
//             posX+=move_unit;
//             char posXString[80]; 
//             sprintf(posXString, "%f", posX); 
//             strcpy(xposFollow, posXString);
//             glFlush();
//             break;

//         case GLUT_KEY_LEFT:
//             posX-=move_unit;;
//         break;

//         case GLUT_KEY_UP:
//             posY+=move_unit;;
//             break;

//         case GLUT_KEY_DOWN:
//             posY-=move_unit;;
//         break;

//         default:
//          break;
//     }
//     glutPostRedisplay();
// }


int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    //Windows tittle is name of program

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    init();
    glutSpecialFunc(keyboardown);
    glutMainLoop();

}