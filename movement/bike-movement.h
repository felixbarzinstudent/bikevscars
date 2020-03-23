#ifndef BIKEMOVEMENT_H
#define BIKEMOVEMENT_H

#include "../graphic/coordinate.h"

/* définition des fonctions */

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