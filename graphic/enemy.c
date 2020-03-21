#include <string.h>
#include <../GL/glut.h>
#include "./enemy.h"
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"
#include "./../utils/calculus.h"
#include "./../utils/timerTools.h"

/* initialisation des variables */
double _timeBetweenEnemyPop = 3;
float _enemySpeedMax = 0.001; //init
float _enemySpeedMin = 0.001; //init

void createEnemies(EnemyList* list) {
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(!timerInitEnemiesFunc(_timeBetweenEnemyPop)) { // crée un ennemi toutes les x secondes
        Enemy* enemy = malloc(sizeof(Enemy));
        enemy->position.x = floatRandom(-0.85, 0.85);
        enemy->position.y = 1;
        enemy->position.z = 0;
        enemy->speed = floatRandom(_enemySpeedMin, _enemySpeedMax);
        enemy->isAlive = true;
        insertEnemyFront(list, enemy);
    }
}

void shootEnemy (EnemyShotList* enemyShotList, Enemy* enemy) {
    if (enemyShotList == NULL)
        exit(EXIT_FAILURE);

    Shot* shot = malloc(sizeof(Shot));
    shot->position.x = enemy->position.x;
    shot->position.y = (enemy->position.y - 0.2);
    shot->position.z = 0;
    shot->speed = (_enemySpeedMin + 0.001);
    insertEnemyShotFront(enemyShotList, shot);
}

void initEnemyFactory() {
    _enemySpeedMax = 0.001;
    _enemySpeedMin = 0.001;
    _timeBetweenEnemyPop = 3;
}