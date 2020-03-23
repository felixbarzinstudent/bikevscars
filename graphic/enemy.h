#ifndef ENEMY_H
#define ENEMY_H
#include <../GL/glut.h>
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"

/* déclaration des variables */

extern double _timeBetweenEnemyPop;
extern float _enemySpeedMax;
extern float _enemySpeedMin;
extern int _madMax;

/* définition des fonctions */

/*
* Cette fonction crée un ennemi pour l'ajouter dans la liste des ennemis
* @Param {list} liste d'ennemis
*/
void createEnemies(EnemyList* list);
/*
* Cette fonction initialise un tir ennemi
*/
void shootEnemy();
/*
* Réinitialise les paramètres de création d'un ennemi
*/
void initEnemyFactory();
/*
* Cette fonction dessine les ennemis
* @Param {texturecar} texture de l'ennemi
* @Param {enemyList} liste d'ennemis qu'il faut dessiner
*/
void drawEnemies(GLuint texturecar, EnemyList* enemyList);
/*
* Cette fonction dessine les tirs des ennemis
* @Param {textureLightBeam} texture du tir ennemi
* @Pram {enemyShotList} liste des tirs ennemis qu'il faut dessiner
*/
void drawEnemiesShots(GLuint textureLightBeam, EnemyShotList* enemyShotList);
#endif