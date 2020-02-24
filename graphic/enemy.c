#include <GL/glut.h>

/* initialisation des variables */
float ennemyPosX = 0, ennemyPosY = 0.5f;
const float ennemyPosZ = 0;

float ennemyEndPosY = -0.5f;

void drawEnemy(){
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.1, 0.2);
        glVertex2f(0.1, 0.2);
        glVertex2f(0.1, -0.2);
    glEnd();
}