#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "./coordinate.h"
#include "./../linked-list/enemy-list.h"

/* définition des structures */
/* Ce struct représente un ennemi présent dans le jeu. Cet ennemi peut bouger et est soit vivant, soit mort */
// typedef struct Enemy Enemy;
// typedef struct Enemy {
//     struct Coordinate position;
//     bool isAlive;
//     int speed;
//     Enemy *next;
//     Enemy *previous;
// } Enemy;
void testtest();
/*
* Cette fonction initialise un ennemi
*/
void initEnemy();

// création des enemis et ajout à la liste des ennemis
void createEnemies(EnemyList* list);

/* Cette fonction définit comment doit être dessiner un ennemi */
//void drawEnemy();

//TODO
/*
* Cette fonction initialise un tir (vitesse de la munition, position... ) et l'insert dans la liste passée
* en paramètre
* @Param {}
* Pré-condition : speed > 0 et ls != NULL
*/
//void shootEnemy(ListShootEnemy list, int speed);
#endif