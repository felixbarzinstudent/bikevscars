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

/*
* fonction qui change les coordonnées d'un objet sur le plan cartesien en fonction de la touche appuyée sur le clavier
* @Param {key} identifie quelle touche a été appuyée
* @Param {x} identifie la position de la souris sur l'axe X au moment ou la touche du clavier est appuyée (UNUSED)
* @Param {y} identifie la position de la souris sur l'axe Y au moment ou la touche du clavier est appuyée (UNUSED)
* Pré-condition :
* Post-condition:
*/
void keyboardownBike(int key, int x, int y);
/*
* Cette fonction initialise le tir : vitesse de la munition, position, ...
* @Param {shotList}
*/
void shoot(List* shotList);
/* Cette fonction définit comment doit être dessiner un ennemi */
//void drawEnemy();

#endif