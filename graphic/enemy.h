#ifndef enemy_H
#define enemy_H
#include "./../linked-list/enemy-list.h"

extern double _timeBetweenEnemyPop;
extern float _enemySpeedMax;
extern float _enemySpeedMin;

void createEnemies(EnemyList* list);
/*
* Cette fonction initialise un tir ennemi
*/
void shootEnemy();
/*
* Réinitialise les paramètres de création d'un ennemi
*/
void initEnemyFactory();
//TODO
/*
* Cette fonction initialise un tir (vitesse de la munition, position... ) et l'insert dans la liste passée
* en paramètre
* @Param {}
* Pré-condition : speed > 0 et ls != NULL
*/
//void shootEnemy(ListShootEnemy list, int speed);
#endif