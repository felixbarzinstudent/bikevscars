#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "character.h"

/* définition des structures */
typedef struct Enemy {
    struct Coordinates position;
    bool isAlive;
} Enemy;

extern struct Enemy _enemy;

/*
* initialisation de la position de l'ennemi
*/
void initEnemy();

/* Cette fonction définit les bases pour dessiner un ennemi */
void drawEnemy();

#endif