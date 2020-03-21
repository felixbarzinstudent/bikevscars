#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include "./text-tools.h"
#include "./../graphic/bike.h"

char _textCollision[18] = "";

void writeOnWindow(float x, float y, char text[], int size, int red, int green, int blue) {
        glColor3f(red, green, blue);
        glRasterPos2f(x, y);// Positionne le texte
        for ( int i = 0; i < size; ++i ) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }
}

void concatArrayOfString(char* string1, char* string2, int sizeString2) {
	 strncat(string1, string2, sizeString2);
}

void displayTopBoardText(Bike* bike, int total) {
	//vies
    if(bike->life >= 1) {
        int size = bike->life * 2;
        char lifeArray[size];
        char lifeText [] = "Vies: ";
        for(int i = 0; i < (size * 2); i++){
            if (i%2 == 0) {
                lifeArray[i] = '|';
            } else {
                lifeArray[i] = ' ';
            }
        }

        concatArrayOfString(lifeText, lifeArray, size);
        writeOnWindow(-1, 0.93, lifeText, 12, 1, 1, 1);
    } else {
        writeOnWindow(-1, 0.93, "GAME OVER", 9, 1, 1, 1);
    }
    
    //score
    char buf[12];
    snprintf(buf, 12, "Points: %d", total);
    writeOnWindow(0.6, 0.93, buf, 10, 1, 1, 1);
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