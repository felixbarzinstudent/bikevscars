#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include "./text-tools.h"
#include "./../graphic/bike.h"

char _textCollision[18] = "";

void writeOnWindow(float x, float y, char text[], int size, int red, int green, int blue) {
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
    glPushMatrix();
        glColor3f(red, green, blue);
        //glClear(GL_COLOR_BUFFER_BIT);
        // glMatrixMode( GL_MODELVIEW );
        // glLoadIdentity();
        glRasterPos2f(x, y);// Positionne le texte
        for ( int i = 0; i < size; ++i ) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void concatArrayOfString(char* string1, char* string2, int sizeString2, char* outPut) {
	 strncat(string1, string2, sizeString2);
}

void displayLife(Bike* bike) {
    glDisable(GL_TEXTURE_2D);
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
	writeOnWindow(-1, 0.9, lifeText, 15, 1, 1, 1);
    glEnable(GL_TEXTURE_2D);
}

void displayBikePositionX(int x, int y, char text[], int windowWidth, int windowHeight) {
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
}

void displayCollision(int x, int y, char text[]) {
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
}

void displayScore(int total) {
    glDisable(GL_TEXTURE_2D);
	//int size = 8;
	//char lifeText [] = "Points: ";
    char buf[12];

    snprintf(buf, 12, "Points: %d", total);
    glColor3f(1,1,1);
    glRasterPos2f(0.6, 0.9);
    for ( int i = 0; i < 11; ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
    }
	//writeOnWindow(0.6, 0.9, buf, 15);
    glEnable(GL_TEXTURE_2D);
}