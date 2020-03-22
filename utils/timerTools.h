/*
* Ce fichier contient des classes qui maintiennent des timers
*/
#ifndef TIMERTOOLS_H
#define TIMERTOOLS_H
#include <stdbool.h>
#include <sys/time.h>
#include "./../structs/enemy-struct.h"

typedef struct Timer {
    bool lock;
    struct timeval start;
    struct timeval stop;
} Timer;

extern Timer timerInitEnemies;
extern Timer timerInvincibility;
extern Timer _timeTimeElapsed;
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
bool timerInvincibilityFunc(double duration);
bool timerInitEnemiesFunc(double duration);
bool timerEnemiesShootFunc(Enemy* enemy, double duration);
bool timerInitObstaclesFunc(double duration);
double getTimeElapsed(int secondsSaved);
#endif