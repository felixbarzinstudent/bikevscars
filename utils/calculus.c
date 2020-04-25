#include <math.h>
#include <stdlib.h>
#include "calculus.h"

float floatRandom(float min, float max)
{
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min );   
}