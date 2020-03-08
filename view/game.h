/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/
#include "./../graphic/enemy.h"

#define WIDTH 500
#define HEIGHT 500
#define XWINDOWPOSITION 0
#define YWINDOWPOSITION 0

/* définition des variables */
int numCurrentWindow;

/* définition des fonctions*/

/*
* Point d’entrée sur la fenêtre du jeu
*/
void windowGame();
/*
* Cette fonction affiche la page du jeu
*/
void vDisplayGame();
/*
* Cette fonction orchestre le déplacement des ennemis depuis le dessus de l'écran vers le bas
*/
void detectCollision();
/*
* Cette fonction est utile lors de la réinitialisation d'une partie
*/
void initGame();
/*
* Cette fonction permet la gestion des touches normales appuyée sur le clavier (espace, ...)
*/
void clavierGame(unsigned char key, int x, int y);
/*
* Cette fonction dessine les tirs dans la fenêtre de jeux
*/
void drawShots();

//TODO
void pointCounter();