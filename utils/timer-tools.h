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

/* définition des fonctions */

/*
* Ces fonctions préfixé par "timer" et post fixé par "Func" initialisent un timer qui renverra true pendant
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
bool timerInitObstaclesFunc(double duration);
bool timerBikeCooldownFunc(double duration);
/* @Param {enemy} permet d'utiliser le timer interne de l'ennemi */
bool timerEnemiesShootFunc(Enemy* enemy, double duration);
/*
* Cette fonction permet d'avoir le temps écoulé depuis le début de la partie
* @Param {secondsSaved} quand on reprend une partie en cours, le temps précédemment parcouru doit être comptabilisé
*/
double getTimeElapsed(int secondsSaved);
/*
* Réinitialise les timers pour recommencer la partie
*/
void resetTimers();
#endif