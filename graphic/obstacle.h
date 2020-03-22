#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <stdbool.h>
#include "./coordinate.h"

typedef struct Obstacle {
    struct Coordinate position;
    bool isBubbled;
    bool isAlive;
} Obstacle;

extern struct Obstacle _obstacle;
extern bool _isAlreadyObstacle;

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