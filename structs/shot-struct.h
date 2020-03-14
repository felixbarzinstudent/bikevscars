#ifndef SHOTSTRUCT_H
#define SHOTSTRUCT_H
#include "./../graphic/coordinate.h"

typedef struct Shot Shot;
struct Shot
{
    struct Coordinate position;
    float speed;
    Shot *next;
    Shot *previous;
};

#endif