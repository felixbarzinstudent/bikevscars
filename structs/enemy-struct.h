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
    TimerTest coolDownShoot;
};
#endif