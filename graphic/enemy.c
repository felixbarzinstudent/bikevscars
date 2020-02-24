#include <GL/glut.h>

/* initialisation des variables */
float ennemyPosX = 0, ennemyPosY = 0;
const float ennemyPosZ = 0;

void drawEnemy(){
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.1, -0.2);
    glVertex2f(-0.1, 0.2);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.1, -0.2);
    glEnd();
}