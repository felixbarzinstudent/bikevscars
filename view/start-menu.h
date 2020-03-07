/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/

#define WIDTH_STARTMENU 500
#define HEIGHT_STARTMENU 500
#define XWINDOWPOSITION_STARTMENU 0
#define YWINDOWPOSITION_STARTMENU 0

/* définition des fonctions*/

/*
* Point d’entrée sur la fenêtre du menu.
*/
void windowMenu();
/*
* Cette fonction initialise les contrôles pour la page de menu
*/
void vClavier_startmenu(unsigned char key, int x, int y);
/*
* Cette fonction permet l'affichage de la page
*/
void vDisplay_startmenu();
/*
* Cette fonction initialise les controles spéciaux pour la page de menu
*/
void vClavierSpecial_startmenu(int key, int x, int y);