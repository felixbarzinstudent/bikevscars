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
void windowGame(int numWindows[]);
void vClavier(unsigned char key, int x, int y);
void vDisplay();
void vReshape();