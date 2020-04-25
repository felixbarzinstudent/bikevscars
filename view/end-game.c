#ifdef	__APPLE_CC__	
#include <GLUT/glut.h>
#else	
#include <GL/glut.h>	
#endif
#include <stdio.h>
#include <string.h>
#include "end-game.h"
#include "navigation.h"
#include "../graphic/bike.h"
#include "../graphic/enemy.h"
#include "../utils/text-tools.h"

/* définititon des variables*/

int activeOptionEndGame = 1;

/* définititon des fonctions */

void vClavier_endgame(unsigned char key, int x, int y);
void vClavierSpecial_endgame(int key, int x, int y);
void vDisplay_endgame();
void displayEndMenu();

void windowEndGame() {
    glutDisplayFunc(vDisplay_endgame);
    glutSpecialFunc(vClavierSpecial_endgame); // up and down
    glutKeyboardFunc(vClavier_endgame); // enter
}

/*
* Cette fonction initialise les controles des touches spéciales pour la page de fin de jeu
* @Param {key} touche du clavier appuyée
* @Param {x} position de la souris sur l'axe x
* @Param {y} position de la souris sur l'axe y
*/
void vClavierSpecial_endgame(int key, int x, int y) 
{
	switch (key){
        case GLUT_KEY_UP:
            activeOptionEndGame -= 1;
            if(activeOptionEndGame < 1)
                activeOptionEndGame = 2;
            break;

        case GLUT_KEY_DOWN:
            activeOptionEndGame += 1;
            if(activeOptionEndGame > 2)
                activeOptionEndGame = 1;
            break;

        default:
        break;
    }
}

/*
* Cette fonction initialise les contrôles sur la page de fin du jeu
* @Param {key} touche du clavier appuyée
* @Param {x} position de la souris sur l'axe x
* @Param {y} position de la souris sur l'axe y
*/
void vClavier_endgame(unsigned char key, int x, int y) {
    if (key == 13) {
        if (activeOptionEndGame == 1)
            setMainCurrentWindow(1); // todo changer le hardcode 1 -> jeu
        else if (activeOptionEndGame == 2)
            setMainCurrentWindow(0); 
    }
}
/*
* Affiche la scene finale du jeu mais sans les commandes pour déplacer le vélo
* Les nouvelles commandes permettent de recommencer une partie ou de revenir au menu de départ
*/
void vDisplay_endgame() {
    displayEndMenu();
}

/*
* Affiche le menu de fin de partie
*/
void displayEndMenu() {
    char option1 [] = "Recommencer";
    char option2 [] = "Quitter";
    
    if(activeOptionEndGame == 1)
        writeOnWindow(-0.2, 0.1, option1, strlen(option1), 0.0, 0.0, 0.0);
    else
        writeOnWindow(-0.2, 0.1, option1, strlen(option1), 0.7, 0.7, 0.7);

    if(activeOptionEndGame == 2)
        writeOnWindow(-0.2, 0.0, option2, strlen(option2), 0.1, 0.1, 0.1);
    else
        writeOnWindow(-0.2, 0.0, option2, strlen(option2), 0.7, 0.7, 0.7);

    glutPostRedisplay();
}