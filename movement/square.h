#ifndef SQUARE_H
#define SQUARE_H

#include "../graphic/character.h"

/* declaration des variables */
extern char _xposRecord[]; // string qui enregistre la position en x de l'objet en mouvement

/*
* life : le nombre de vie restante du carré
* state : le carré devient invincible après avoir perdu une vie. Je pourrais ajouter d'autres bonus de ce genre
* invincibilityDuration : ce temps d'invincibilité est propre au carré, il déterminera le temps d'invincibilité + sprite
*/
typedef struct Square {
    struct Coordinates position;
    int life;
    int state; // bonus in game : état invincible (1), état plus rapide, ...
    int invincibilityDuration;
} Square;

extern struct Square _square;

/*
* Cette fonction initialise la position du square
*/
void initSquare();

/*
* Cette fonction formate les coordonnées recues en paramètre pour permettre l'affichage en temps réel de la position à l'écran
* Cette fonction est utilie pendant le développement de l'application. Elle ne sera probablement plus utilisée après
* @Param {coordinate} coordonnée de l'objet qui doit être affichée
* Pré-condition :
* Post-condition:
*/
void formatCoordinates(float coordinate);

/*
* Cette fonction empêche qu'une coordonnée soit plus grande que 1 pour que l'objet ne puisse pas sortir de la fenêtre
* @Param {coordinate} coordonnée vers laquelle l'objet sera déplacé
* Pré-condition :
* Post-condition:
*/
float cantGoOut(float coordinate);

/*
* Cette fonction retire une vie au carré. Fin du jeu si plus de vies.
* @Param {square} le carré qui doit perdre une vie
* Pré-condition :
* Post-condition:
*/
int lifeLoss(Square* square);

//TODO
void lifeGain(Square* square);
//TODO
void pointGain();

#endif