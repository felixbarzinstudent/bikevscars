/*
* Ce fichier contient les éléments de bases, les éléments communs à toutes fenêtre
* Les nouvelles fenêtres doivent implémenter ce fichier
*/

#define WIDTH_ENDGAME 500
#define HEIGHT_ENDGAME 500


/* définition des fonctions*/

/*
* Point d'entrée sur la fenêtre de jeu
*/
void windowEndGame();
/*
* Cette fonction initialise les contrôles sur la page de fin du jeu
* @Param {key} touche du clavier appuyée
* @Param {x} position de la souris sur l'axe x
* @Param {y} position de la souris sur l'axe y
*/
void vClavier_endgame(unsigned char key, int x, int y);
/*
* Cette fonction affiche la page de fin de jeux
*/
void vDisplay_endgame();
/*
* Cette fonction initialise les controles des touches spéciales pour la page de fin de jeu
* @Param {key} touche du clavier appuyée
* @Param {x} position de la souris sur l'axe x
* @Param {y} position de la souris sur l'axe y
*/
void vClavierSpecial_endgame(int key, int x, int y);
/*
* Dessine le vélo à la position ou il était au moment ou il a perdu sa dernière vie
*/
void drawBike_endgame();
