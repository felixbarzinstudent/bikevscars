/*
* Cette struct représente le tir d'un ennemi ou du vélo.
* Le vélo a un tire classique et un tire bulle. C'est pourquoi il y a une propriété 'type'
*/

#ifndef SHOTSTRUCT_H
#define SHOTSTRUCT_H
#include "../graphic/coordinate.h"

typedef struct Shot Shot;
struct Shot
{
    struct Coordinate position;
    float speed;
    int type;
    Shot *next;
    Shot *previous;
};

#endif