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
*/
void writeOnWindow(float x, float y, char text[], int size);
/*
* Cette fonction affiche la vie restante du carré
* @Param {square} objet dont la vie doit être affichée
*/
void displayLife(Square* square);
/*
* Cette fonction affiche le texte des collisions
* @Param {x} position en X sur la fenêtre
* @Param {y} position en Y sur la fenêtre
* @Param {text} chaîne de caractère représentant le texte qui doit être affiché
*/
void displayCollision(int x, int y, char text[]);
/*
* Cette fonction affiche le texte représentant la position du carré en X
* @Param {x} position en X sur la fenêtre
* @Param {y} position en Y sur la fenêtre
* @Param {text} chaîne de caractère représentant le texte qui doit être affiché
* @Param {windowWidth} largeur de la fenêtre
* @Param {windowHeight} largeur de la fenêtre
*/
void displaySquarePositionX(int x, int y, char text[], int windowWidth, int windowHeight);