#ifndef BIKE_H
#define BIKE_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "coordinate.h"

/* declaration des variables */

/* définition des structures */

/*
* life : le nombre de vie restante du vélo
* state : le vélo devient invincible après avoir perdu une vie. Je pourrais ajouter d'autres bonus de ce genre
* invincibilityDuration : ce temps d'invincibilité est propre au vélo, il déterminera le temps d'invincibilité + sprite
*/
typedef struct Bike {
    struct Coordinate position;
    int life;
    int state; // bonus in game : état invincible (1), état plus rapide, ...
    int invincibilityDuration;
} Bike;

extern struct Bike _bike;

/*
* Cette fonction initialise la position du bike
*/
void initBike();

/*
* Cette fonction retire une vie au carré. Fin du jeu si plus de vies.
* @Param {bike} le carré qui doit perdre une vie
* Pré-condition :
* Post-condition:
*/
int lifeLoss(Bike* bike);

//TODO
void lifeGain(Bike* bike);
//TODO
void pointGain();

/* Cette fonction définit comment doit être dessiner un ennemi */
void drawEnemy();

#endif