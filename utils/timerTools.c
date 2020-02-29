#include <stdbool.h>
#include "timerTools.h"

Timer timerInvincibility;
long int timerInvincibilitySeconds = 0;
long int timerInvincibilitySecondsLater = 0;
long int timerInvincibilityLock = false;

bool timerInvincibilityFunc(int duration) {
    timerInvincibility.secondsLater = time(NULL);

    if(timerInvincibility.seconds != 0 && (timerInvincibility.secondsLater - timerInvincibility.seconds) > duration){
        timerInvincibility.lock = false;
        timerInvincibility.seconds = 0;//reset
        timerInvincibilityLock = false;//reset
        return false;
    }

    if (!timerInvincibility.lock) { 
            timerInvincibility.lock = true;
            timerInvincibility.seconds = time(NULL); 
            return true;
        }
    return true;
}