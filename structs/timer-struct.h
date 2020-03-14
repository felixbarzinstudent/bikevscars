#ifndef TIMERSTRUCT_H
#define TIMERSTRUCT_H
#include <sys/time.h>

typedef struct TimerTest TimerTest;
struct TimerTest {
    bool lock;
    struct timeval start;
    struct timeval stop;
};

#endif