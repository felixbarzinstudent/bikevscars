/*
* Cette structure représente un ennemi. Un ennemi est une voiture. Il a uen vitesse, il est en vie ou non.
* L'ennemi peut tirer mais ne peut pas enchainer les tirs grâce au cooldown.
*/

#ifndef ENEMYSTRUCT_H
#define ENEMYSTRUCT_H
#include "./timer-struct.h"
#include "./../graphic/coordinate.h"

typedef struct Enemy Enemy;
struct Enemy {
    struct Coordinate position;
    bool isAlive;
    float speed;
    Enemy *next;
    Enemy *previous;
    TimerEnemy coolDownShoot; // empeche les ennemis d'enchainer les tirs trop vite
};
#endif