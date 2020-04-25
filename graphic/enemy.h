#ifndef ENEMY_H
#define ENEMY_H
#include <../GL/glut.h>
#include "./../linked-list/enemy-list.h"
#include "./../linked-list/enemy-shot-list.h"

/* déclaration des variables */

extern double _timeBetweenEnemyPop; // délais d'attente entre l'apparition de chaque ennemi
extern float _enemySpeedMax;
extern float _enemySpeedMin;
extern int _madMax; // agressivité de la voiture (suivre la trajectoire du vélo)

/* définition des fonctions */

/*
* Cette fonction crée un ennemi pour l'ajouter dans la liste des ennemis
* @Param {list} liste d'ennemis
* @Param {textureCar} texture d'une voiture rouge
* @Param {textureAudi} texture d'une audi rouge
* @Param {textureMiniTruck} texture d'un pick up
* @Param {textureMiniVan} texture d'un mini van
* @Param {textureViper} texture d'une voiture de course
* @Param {textureTaxi} texture d'un taxi
*/
void createEnemies(EnemyList* list, GLuint textureCar, GLuint textureAudi, GLuint textureMiniTruck, GLuint textureMiniVan, GLuint textureViper, GLuint textureTaxi);
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
* @Param {enemyList} liste d'ennemis qu'il faut dessiner
*/
void drawEnemies(EnemyList* enemyList);
/*
* Cette fonction dessine les tirs des ennemis
* @Param {textureLightBeam} texture du tir ennemi
* @Pram {enemyShotList} liste des tirs ennemis qu'il faut dessiner
*/
void drawEnemiesShots(GLuint textureLightBeam, EnemyShotList* enemyShotList);
#endif