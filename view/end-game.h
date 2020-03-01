/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/

#define WIDTH_ENDGAME 500
#define HEIGHT_ENDGAME 500
#define XWINDOWPOSITION_ENDGAME 0
#define YWINDOWPOSITION_ENDGAME 0

/* définition des variables */

/* définition des fonctions*/

/*
* Correspond à l'entrée, au main, de la fenêtre
*/
void windowEndGame(int numeroWindows[]);
void vClavier_endgame(unsigned char key, int x, int y);
void vDisplay_endgame();
void vReshape_endgame();