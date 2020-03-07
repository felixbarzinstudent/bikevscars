#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "character.h"

/* définition des structures */
/* Ce struct représente un ennemi présent dans le jeu. Cet ennemi peut bouger et est soit vivant, soit mort */
typedef struct Enemy {
    struct Coordinates position;
    bool isAlive;
} Enemy;

extern struct Enemy _enemy;

/*
* initialisation de la position de l'ennemi et de son état (mort ou vivant)
*/
void initEnemy();

/* Cette fonction définit comment doit être dessiner un ennemi */
void drawEnemy();

#endif