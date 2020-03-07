#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include "./text-tools.h"
#include "./../graphic/bike.h"

char _textCollision[18] = "";

void writeOnWindow(float x, float y, char text[], int size) {
    glColor3f(1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glRasterPos2f(x, y);// Positionne le texte
    for ( int i = 0; i < size; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void concatArrayOfString(char* string1, char* string2, int sizeString2, char* outPut) {
	 strncat(string1, string2, sizeString2);
}

void displayLife(Bike* bike) {
	int size = 6;
	char lifeText [] = "Life: ";
	char lifeArray[size];
	for(int i = 0; i < ((bike->life) * 2); i++){
		if (i%2 == 0) {
			lifeArray[i] = '|';
		} else {
			lifeArray[i] = ' ';
		}
	}
	char outPut[100];

	concatArrayOfString(lifeText, lifeArray, size, outPut);
	writeOnWindow(-1, 0.9, lifeText, 15);
}

void displayBikePositionX(int x, int y, char text[], int windowWidth, int windowHeight) {
    glColor3f(1,1,1);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D( 0, windowWidth, 0, windowHeight );
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
             glRasterPos2i(x, y);// Positionne le texte
             for ( int i = 0; i < 12; ++i )
             {
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
             }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}

void displayCollision(int x, int y, char text[])
{
    glPushMatrix();
    glColor3f(1,1,1);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
             glRasterPos2f(x, y);//Positionne le texte
             for ( int i = 0; i < 18; ++i )
             {
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
             }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}