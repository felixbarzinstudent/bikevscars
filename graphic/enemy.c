#include <GL/glut.h>
#include "enemy.h"

/* initialisation des variables */
struct Enemy _enemy;

void initEnemy() {
    _enemy.position.x = -0.75;
    _enemy.position.y = 0;
    _enemy.position.z = 0;
    _enemy.isAlive = true;
}

void drawEnemy(){
    glBegin(GL_POLYGON);
        if(_enemy.isAlive == true)
            glColor3f(0.0, 1.0, 0.0);
        else
            glColor4f(0.0, 1.0, 0.0, 0.1);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.1, 0.2);
        glVertex2f(0.1, 0.2);
        glVertex2f(0.1, -0.2);
    glEnd();
}