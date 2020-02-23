#ifndef SQUARE_H
#define SQUARE_H

/* declaration des variables */
extern float posX;
extern float posY;
extern float posZ;
extern char xposRecord[];

/*
* fonction qui change les coordonnées d'un objet sur le plan cartesien en fonction de la touche appuyée sur le clavier
* @Param {key} identifie quelle touche a été appuyée
* @Param {x} identifie la position de la souris sur l'axe X au moment ou la touche du clavier est appuyée (UNUSED)
* @Param {y} identifie la position de la souris sur l'axe Y au moment ou la touche du clavier est appuyée (UNUSED)
* Pré-condition :
* Post-condition:
*/
void keyboardown(int key, int x, int y);

#endif