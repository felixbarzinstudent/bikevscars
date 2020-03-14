#ifndef enemy_H
#define enemy_H
#include "./../linked-list/enemy-list.h"

extern double timeBetweenEnemyPop;
extern float enemySpeedMax;
extern float enemySpeedMin;

void createEnemies(EnemyList* list);
/*
* Cette fonction initialise un tir ennemi
*/
void shootEnemy();

//TODO
/*
* Cette fonction initialise un tir (vitesse de la munition, position... ) et l'insert dans la liste passée
* en paramètre
* @Param {}
* Pré-condition : speed > 0 et ls != NULL
*/
//void shootEnemy(ListShootEnemy list, int speed);
#endif