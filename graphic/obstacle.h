/*
* Fichier contenant les fonctions et les variables nécéssaires à la création d'un obstacle.
*
* Un obstacle est représenté par une voiture de police placée en travers de la route. Elle ne 
* se déplace pas mais si le vélo la touche il perd une vie. Si les ennemis la touche ils meurent.
* L'obstacle apparait de manière aléatoire sur le haut de l'écran.
* Le tir 'bubble' du vélo permet de rendre l'obstacle vulnérable aux tirs classiques. Les tirs
* ennemis passent au travers de l'obstacle.
*
* Il ne peut y avoir qu'un obstacle à la fois sur l'écran de jeux.
*/

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <stdbool.h>
#include "coordinate.h"

/*
* Cet obstacle peut être emprisonné dans une bulle (tir spécial du vélo) et peut ensuite 
* être détruit. Quand un tire entre en collision avec l’obstacle, les propriétés 
* « isBubbled » et « isAlive » sont vérifiées
*/
typedef struct Obstacle {
    struct Coordinate position;
    bool isBubbled;
    bool isAlive;
} Obstacle;

extern struct Obstacle _obstacle;
extern bool _isAlreadyObstacle; // il ne peut y avoir qu'un obstacle à la fois sur l'écran de jeu

/*
* Cette fonction positionne l'obstacle sur la route
* Post-condition : un objet obstacle doit être initialisé avec des coordonnées
*/
void createObstacle();
/*
* Cette fonction dessine l'obstale sur la route
* @Param {roadSpeed} L'obstacle doit "avancer" au même rythme que la route
* @Param {texturePolice1} Texture de la voiture de police ayant le gyrophare rouge allumé
* @Param {texturePolice2} Texture de la voiture de police ayant le gyrophare central allumé
* @Param {texturePolice3} Texture de la voiture de police ayant le gyrophare bleu allumé
* @Param {textureBubble} Texture de la bulle qui va enrober la voiture de police
* Post-condition : une voiture doit etre dessiné en travers de la route
*/
void drawObstacle(float roadSpeed, GLuint texturePolice1, GLuint texturePolice2, GLuint texturePolice3, GLuint textureBubble);

#endif