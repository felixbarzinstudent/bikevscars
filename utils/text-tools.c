#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include "./text-tools.h"
#include "./../graphic/bike.h"
#include "./../utils/timer-tools.h"

char _textCollision[18] = "";

void writeOnWindow(float x, float y, char text[], int size, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);// Positionne le texte
    for (int i = 0; i < size; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void concatArrayOfString(char* string1, char* string2, int sizeString2) {
	strncat(string1, string2, sizeString2);
}

void displayTopBoardText(Bike* bike, int total, int secondsSaved) {
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
    char buf[5];
    char linePoints[12] = "Points : ";
    sprintf(buf, "%i", total);
    strcat(linePoints, buf);
    writeOnWindow(0.6, 0.93, linePoints, strlen(linePoints), 1, 1, 1);

    //time
    int seconds = (int) getTimeElapsed(secondsSaved);
    char bufSeconds[10];
    char lineSecondes[5] = " sec.";
    sprintf(bufSeconds, "%i", seconds);
    strcat(bufSeconds, lineSecondes);
    
    if (seconds < 10)
        writeOnWindow(-0.11, 0.93, bufSeconds, 6, 1, 1, 1);
    else if (seconds < 100)
        writeOnWindow(-0.11, 0.93, bufSeconds, 7, 1, 1, 1);
    else if (seconds < 1000)
        writeOnWindow(-0.11, 0.93, bufSeconds, 8, 1, 1, 1);
}