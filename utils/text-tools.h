/*
* Ce fichier contient des fonctions qui formattent et affiche du texte sur la fenre
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include "./../graphic/bike.h"

/* définition des fonctions */

/*
* Cette fonction écrit un texte sur la fenêtre à une position donnée
* @Param {x} position en X sur la fenêtre
* @Param {y} position en Y sur la fenêtre
* @Param {text} chaîne de caractère représentant le texte qui doit être affiché
* @Param {size} taille de la chaîne de caractère
* Pré-condition: size == taille de text[]
*/
void writeOnWindow(float x, float y, char text[], int size, float red, float green, float blue);
/*
* Cette fonction affiche la vie restante du vélo et le score
* @Param {bike} objet dont la vie doit être affichée
* @Param {total} le score total
* @Param {secondsSaved} temps déja parcouru récupéré d'une sauvegarde
*/
void displayTopBoardText(Bike* bike, int total, int secondsSaved);