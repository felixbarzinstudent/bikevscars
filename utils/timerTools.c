#include <stdbool.h>
#include "timerTools.h"
#include <../GL/glut.h>

Timer timerInvincibility;

bool timerInvincibilityFunc(int duration) {
    if (duration < 1) 
        exit(EXIT_FAILURE);

    timerInvincibility.secondsLater = time(NULL);

    if(timerInvincibility.seconds != 0 && (timerInvincibility.secondsLater - timerInvincibility.seconds) > duration){
        timerInvincibility.lock = false;//reset
        timerInvincibility.seconds = 0;//reset
        return false;
    }

    if (!timerInvincibility.lock) { 
            timerInvincibility.lock = true;
            timerInvincibility.seconds = time(NULL); 
            return true;
        }

    return true;
}

Timer timerInitEnemies;

bool timerInitEnemiesFunc(int duration) {
    if (duration < 1) 
        exit(EXIT_FAILURE);

    timerInitEnemies.secondsLater = time(NULL);

    if(timerInitEnemies.seconds != 0 && (timerInitEnemies.secondsLater - timerInitEnemies.seconds) > duration){
        timerInitEnemies.lock = false;//reset
        timerInitEnemies.seconds = 0;//reset
        return false;
    }

    if (!timerInitEnemies.lock) { 
            timerInitEnemies.lock = true;
            timerInitEnemies.seconds = time(NULL); 
            return true;
        }

    return true;
}