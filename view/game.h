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
* Cette fonction permet la gestion des touches normales appuyée sur le clavier (espace, ...)
*/
void clavierGame(unsigned char key, int x, int y);
/*
* Cette fonction dessine les tirs dans ka fenêtre de jeux
*/
void drawShots();