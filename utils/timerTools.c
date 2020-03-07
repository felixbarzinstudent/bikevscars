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