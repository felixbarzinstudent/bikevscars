/*
* Ce fichier contient des fonctions qui formattent et affiche du texte sur la fenre
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include "./../graphic/bike.h"

extern char _textCollision[18];

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
*/
void displayTopBoardText(Bike* bike, int total);

/*
* Cette fonction affiche le score
* @Param {_totalPoints} nombre qu'il faut afficher
*/
void displayScore(int _totalPoints);