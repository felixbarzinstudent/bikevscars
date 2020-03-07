#ifndef BIKEMOVEMENT_H
#define BIKEMOVEMENT_H

#include "../graphic/coordinate.h"

// /* declaration des variables */
extern char _xposRecord[]; // string qui enregistre la position en x de l'objet en mouvement (utilisé pendant le développement)

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
*/
float cantGoOut(float coordinate);

/*
* Cette fonction change les coordonnées d'un objet sur le plan cartesien en fonction de la touche appuyée sur 
* le clavier (haut, bas, gauche, droite)
* @Param {key} identifie quelle touche a été appuyée
* @Param {x} identifie la position de la souris sur l'axe X au moment ou la touche du clavier est appuyée (UNUSED)
* @Param {y} identifie la position de la souris sur l'axe Y au moment ou la touche du clavier est appuyée (UNUSED)
*/
void keyboardownBike(int key, int x, int y);
#endif