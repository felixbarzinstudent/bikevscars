#include <string.h>
#include <../GL/glut.h>
#include "./enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
double timeBetweenEnemyPop = 3;
float enemySpeedMax = 0.0005; //init
float enemySpeedMin = 0.0005; //init

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

void shootEnemy (EnemyShotList* enemyShotList, Enemy* enemy) {
    if (enemyShotList == NULL)
        exit(EXIT_FAILURE);

    Shot shot;
    shot.position.x = enemy->position.x;
    shot.position.y = enemy->position.y;
    shot.position.z = 0;
    shot.speed = 0.001;
    insertEnemyShotFront(enemyShotList, shot);
}