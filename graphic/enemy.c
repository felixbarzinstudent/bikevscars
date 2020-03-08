#include <GL/glut.h>
#include "enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
//struct Enemy _enemy; // TODO : remove
const int timeBetweenEnemyPop = 3;

// void initEnemy() {
//     _enemy.position.x = -0.75;
//     _enemy.position.y = 0;
//     _enemy.position.z = 0;
//     _enemy.isAlive = true;
// }
void testtest() {
    printf("coucou");
}

void createEnemies(EnemyList* list) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(timeBetweenEnemyPop)) { // crée un ennemi toutes les 3 secondes
        Enemy enemy;
        enemy.position.x = floatRandom(-0.70, 0.70);
        enemy.position.y = 1;
        enemy.position.z = 0;
        enemy.speed = 0.001;
        enemy.isAlive = true;
        insertEnemyFront(list, enemy);
    }
}

// void drawEnemy(){
//     glBegin(GL_POLYGON);
//         if(_enemy.isAlive == true)
//             glColor3f(0.0, 1.0, 0.0);
//         else
//             glColor4f(0.0, 1.0, 0.0, 0.1);
//         glVertex2f(-0.1, -0.2);
//         glVertex2f(-0.1, 0.2);
//         glVertex2f(0.1, 0.2);
//         glVertex2f(0.1, -0.2);
//     glEnd();
// }