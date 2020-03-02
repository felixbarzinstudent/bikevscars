/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/

#define WIDTH 500
#define HEIGHT 500
#define XWINDOWPOSITION 0
#define YWINDOWPOSITION 0

/* définition des variables */
int numCurrentWindow;

/* définition des fonctions*/

/*
* Correspond à l'entrée, au main, de la fenêtre
*/
void windowGame();
/*
* Cette fonction affiche la page de fin de jeux
* Pré-condition :
* Post-condition:
*/
void vDisplayGame();
/*
* Cette fonction orchestre le déplacement des ennemis depuis le dessus de l'écran vers le bas
* Pré-condition :
* Post-condition:
*/
void moveVertical();
/*
* Cette fonction est utile lors de la réinitialisation d'une partie
* Pré-condition :
* Post-condition:
*/
void initGame();
/*
* fonction qui change les coordonnées d'un objet sur le plan cartesien en fonction de la touche appuyée sur le clavier
* @Param {key} identifie quelle touche a été appuyée
* @Param {x} identifie la position de la souris sur l'axe X au moment ou la touche du clavier est appuyée (UNUSED)
* @Param {y} identifie la position de la souris sur l'axe Y au moment ou la touche du clavier est appuyée (UNUSED)
* Pré-condition :
* Post-condition:
*/
void keyboardownGame(int key, int x, int y);
/*
* Cette fonction permet la gestion des touches normales appuyée sur le clavier (espace, ...)
*/
void clavierGame(unsigned char key, int x, int y);
/*
* Cette fonction initialise le tir : vitesse de la munition, position, ...
*/
void shoot();
/*
* Cette fonction dessine les tirs dans ka fenêtre de jeux
*/
void drawShots();