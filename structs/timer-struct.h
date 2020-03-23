/*
* Les timer permettent de gérer les éléments qui ont des effet dans le temps (cooldown, temps d'apparition, ...)
*/

#ifndef TIMERSTRUCT_H
#define TIMERSTRUCT_H
#include <sys/time.h>

typedef struct TimerEnemy TimerEnemy;
struct TimerEnemy {
    bool lock;
    struct timeval start;
    struct timeval stop;
};

#endif