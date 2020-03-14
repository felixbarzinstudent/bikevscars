#ifndef BIKE_H
#define BIKE_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "coordinate.h"
#include "./../linked-list/shot-list.h"

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
    double invincibilityDuration;
} Bike;

extern struct Bike _bike;

/*
* Cette fonction initialise les propriétés du vélo
*/
void initBike();

/*
* Cette fonction retire une vie au vélo. Return 1 si le vélo n'a plus de vie.
* @Param {bike} le vélo qui doit perdre une vie
* Pré-condition : bike->life > 0
* Post-condition: /
*/
int lifeLoss(Bike* bike);

//TODO
/*
* Ajoute une vie au compteur de vie du vélo
*/
void lifeGain(Bike* bike);

/*
* Cette fonction initialise un tir (vitesse de la munition, position... ) et l'insert dans la liste passée
* en paramètre
* @Param {shotList}
* Pré-condition: shotList != NULL
*/
void shoot(List* shotList);

#endif