#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <../GL/glut.h>
#include "timerTools.h"

Timer timerInvincibility;
bool timerInvincibilityFunc(double duration) {
    if (duration < 0) 
        exit(EXIT_FAILURE);

    gettimeofday(&timerInvincibility.stop, NULL);
    if(timerInvincibility.start.tv_usec > 0) {
        double seconds = (double)(timerInvincibility.stop.tv_usec - timerInvincibility.start.tv_usec) / 1000000 + (double)(timerInvincibility.stop.tv_sec - timerInvincibility.start.tv_sec);
        if(seconds >= duration){
            timerInvincibility.lock = false;//reset
            timerInvincibility.start.tv_usec = 0;//reset
            printf("Finished in %f sec\n", seconds); 
            return false;
        }
    }    

    if (!timerInvincibility.lock) { 
        timerInvincibility.lock = true;
        timerInvincibility.start = timerInvincibility.stop; 
        return true;
    }

    return true;
}
Timer timerInitEnemies;
bool timerInitEnemiesFunc(double duration) {
    if (duration < 0)
        exit(EXIT_FAILURE);

    gettimeofday(&timerInitEnemies.stop, NULL);
    if(timerInitEnemies.start.tv_usec > 0) {
        double seconds = (double)(timerInitEnemies.stop.tv_usec - timerInitEnemies.start.tv_usec) / 1000000 + (double)(timerInitEnemies.stop.tv_sec - timerInitEnemies.start.tv_sec);
        if(seconds >= duration){
            timerInitEnemies.lock = false;//reset
            timerInitEnemies.start.tv_usec = 0;//reset
            //printf("Finished in %f sec\n", seconds); 
            return false;
        }
    }    

    if (!timerInitEnemies.lock) { 
        timerInitEnemies.lock = true;
        timerInitEnemies.start = timerInitEnemies.stop; 
        return true;
    }

    return true;
}