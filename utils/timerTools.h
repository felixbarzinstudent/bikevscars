/*
* Ce fichier contient des classes qui maintiennent des timers
*/
#include <time.h>
#include <stdbool.h>

typedef struct Timer {
    time_t seconds;
    time_t secondsLater;
    bool lock;
} Timer;

/*
* Cette fonction initialise un timer qui renverra true pendant
* la durée passée en paramètre. Renvoit faux ensuite.
* @Param {duration} durée du timer
*/
bool timerInvincibilityFunc(int duration);