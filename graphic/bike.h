#ifndef BIKE_H
#define BIKE_H
#ifdef	__APPLE_CC__	
#include <GLUT/glut.h>	
#else	
#include <GL/glut.h>	
#endif
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "coordinate.h"
#include "../linked-list/shot-list.h"

/* declaration des variables */

extern const int _sonicWaveShot; //tir normal
extern const int _bubbleShot; // tir bulle


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
    double invincibilityDuration; // définit le temps d’invincibilité que peut avoir un vélo à la suite de la perte d’une vie.
} Bike;

extern struct Bike _bike;

/* définition des fonctions */

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

/*
* Cette fonction initialise un tir (vitesse de la munition, position... ) et l'insert dans la liste passée
* en paramètre
* @Param {shotList}
* @Param {type} spécifie le type de tir qui est demandé (sonicwave ou bubble)
* Pré-condition: shotList != NULL
*/
void shoot(List* shotList, int type);

/*
* Dessine les tirs du vélo
* @Param {textureWave} texture du tir normal
* @Param {textureBubble} texture du tir bulle
* @Param {shotList} liste des tirs du vélo
*/
void drawShots(GLuint textureWave, GLuint textureBubble, List *shotList);

/*
* Dessine le vélo
* @Param {texture} texture du vélo
*/
void drawBike(GLuint texture);
#endif