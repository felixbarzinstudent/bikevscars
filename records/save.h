#ifndef SAVE_H
#define SAVE_H

/*
* Enregistre le score dans le fichier des meilleurs score si celui-ci est un des meilleurs
* @Param {score} le score de la partie
* Post-condition : les données doivent être écrites dans le fichier
*/
void saveHighscores(int score);
/*
* Lire le fichier des meilleurs score et récupère les meilleus
* Pré-condition : le fichier doit exister
*/
void getTop(int* tab);
/*
* Enregistre les points et la vie dans le fichier des checkpoints.
* Ce fichier sera lu pour reprendre une partie à partir de ce palier.
* Post-condition : les données doivent être écrites dans le fichier
*/
void saveCheckpoint(int points, int life, double seconds);
/*
* Récupere dans le fichier checkpoint le nombre de vie restante lors du dernier passage de palier
* Post-condition : la valeure retournée doit être plus grande que zero
*/
int getLifeFromLastCheckpoint();
/*
* Récupère dans le fichier checkpoint le nombre de point lors du passage au checkpoint
* Post-condition : le modulo du total des points doit être égal à 0
*/
int getPointsFromLastCheckpoint();

void getHighscores(int highscores[], int number);

int getTimeFromLastCheckpoint();
#endif