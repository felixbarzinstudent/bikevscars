#include <../GL/glut.h>
#include <string.h>
#include "./enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
double timeBetweenEnemyPop = 1;
float enemySpeedMax = 0.001; //init
float enemySpeedMin = 0.001; //init

void createEnemies(EnemyList* list) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(timeBetweenEnemyPop)) { // crée un ennemi toutes les x secondes
        Enemy enemy;
        enemy.position.x = floatRandom(-0.70, 0.70);
        enemy.position.y = 1;
        enemy.position.z = 0;
        enemy.speed = floatRandom(enemySpeedMin, enemySpeedMax);
        enemy.isAlive = true;
        insertEnemyFront(list, enemy);
    }
}