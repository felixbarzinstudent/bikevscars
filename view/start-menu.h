/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/

#define WIDTH_STARTMENU 500
#define HEIGHT_STARTMENU 500
#define XWINDOWPOSITION_STARTMENU 0
#define YWINDOWPOSITION_STARTMENU 0

/* définition des variables */
int numWindow;

/* définition des fonctions*/

/*
* Correspond à l'entrée, au main, de la fenêtre
*/
void windowMenu(int numeroWindows[]);
void vClavier_startmenu(unsigned char key, int x, int y);
void vDisplay_startmenu();
void vReshape_startmenu();