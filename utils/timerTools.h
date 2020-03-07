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
* Détails : au lancement du timer, le temps est enregistré dans la propriété seconds du struct et l’accès à 
*           cette initialisation n’est plus possible dès le deuxième passage dans cette fonction car le 
*           booléen «lock » a été changé. Cette fonction ne fera plus rien tant que le temps écoulé n’a pas 
*           dépassé le temps passé en paramètre. La fonction renverra alors « true » et réinitialise le compteur
* @Param {duration} durée du timer
* Pré-condition: duration > 0
*/
bool timerInvincibilityFunc(int duration);