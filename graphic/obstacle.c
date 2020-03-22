#include <../GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./obstacle.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"
#include <stdio.h>

/* déclaration des variables */
bool _isAlreadyObstacle = false;
int minTimeBetweenObstacles = 4; //secondes
struct Obstacle _obstacle;

void createObstacle() {
    if(!_isAlreadyObstacle) {
        if(!timerInitObstaclesFunc(minTimeBetweenObstacles)) { // crée un ennemi toutes les x secondes
        
            // dans le but de ne pas créer un obstacle toute les 5 secondes précisément j'ajoute un peu de random
            srand(time(NULL));
            int r = rand() % 9; //random int between 0 and 9
            if (r < 6) {
                _obstacle.position.x = floatRandom(-0.80, 0.80);
                _obstacle.position.y = 1;
                _obstacle.position.z = 0;
                _obstacle.isBubbled = false;
                _obstacle.isAlive = true;
                _isAlreadyObstacle = true;
                printf("obstacle created \n");
            }
        }
    }
}
int counterTexture = 0;
void drawObstacle(float roadSpeed, GLuint texturePolice1, GLuint texturePolice2, GLuint texturePolice3, GLuint textureBubble) {
    counterTexture++;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Pour les gyrophares de la voiture de police qui fait obstacle
    if(counterTexture >= 0 && counterTexture < 33)
        glBindTexture(GL_TEXTURE_2D, texturePolice1);
    else if(counterTexture < 66 || counterTexture < 0)
        glBindTexture(GL_TEXTURE_2D, texturePolice2);
    else {
        glBindTexture(GL_TEXTURE_2D, texturePolice3);
        if(counterTexture >= 100)
        counterTexture = -33;
    }

    if (_isAlreadyObstacle) {
        glPushMatrix();
            glColor4f(1.0, 1.0, 1.0, 1);

            if(_obstacle.isAlive)
                _obstacle.position.y -= (roadSpeed + 0.0003);
            else
                _obstacle.position.y = -1.2;

            if (_obstacle.isBubbled) {
                glColor4f(1.0, 1.0, 1.0, 0.25);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
                glTranslatef(_obstacle.position.x, _obstacle.position.y, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 1); glVertex2f(-0.2, -0.1);//en bas a gauche
                    glTexCoord2f(0, 1); glVertex2f(-0.2, 0.1);// au dessus a gauche
                    glTexCoord2f(0, 0); glVertex2f(0.2, 0.1);//au dessus à droite
                    glTexCoord2f(1, 0); glVertex2f(0.2, -0.1);//en bas a droite
                glEnd();
                glBindTexture(GL_TEXTURE_2D, textureBubble);
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 1); glVertex2f(-0.2, -0.2);//en bas a gauche
                    glTexCoord2f(0, 1); glVertex2f(-0.2, 0.2);// au dessus a gauche
                    glTexCoord2f(0, 0); glVertex2f(0.2, 0.2);//au dessus à droite
                    glTexCoord2f(1, 0); glVertex2f(0.2, -0.2);//en bas a droite
                glEnd();
            } else {
                glTranslatef(_obstacle.position.x, _obstacle.position.y, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 1); glVertex2f(-0.2, -0.1);//en bas a gauche
                    glTexCoord2f(0, 1); glVertex2f(-0.2, 0.1);// au dessus a gauche
                    glTexCoord2f(0, 0); glVertex2f(0.2, 0.1);//au dessus à droite
                    glTexCoord2f(1, 0); glVertex2f(0.2, -0.1);//en bas a droite
                glEnd();
            }

        glPopMatrix();
        if(_obstacle.position.y < -1.2)
            _isAlreadyObstacle = false;
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}