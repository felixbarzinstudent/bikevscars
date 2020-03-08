#include <../GL/glut.h>
#include <string.h>
#include "./enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
const int timeBetweenEnemyPop = 1;

void createEnemies(EnemyList* list) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(timeBetweenEnemyPop)) { // crée un ennemi toutes les x secondes
        Enemy enemy;
        enemy.position.x = floatRandom(-0.70, 0.70);
        enemy.position.y = 1;
        enemy.position.z = 0;
        enemy.speed = 0.001;
        enemy.isAlive = true;
        insertEnemyFront(list, enemy);
    }
}