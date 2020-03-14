/*
* Interface pour une liste chainée
* Mon implémentation de cette interface se trouve dans le fichier shotList.c
*/

#ifndef ENEMYSHOTLIST_H
#define ENEMYSHOTLIST_H
#include "./../structs/shot-struct.h"

typedef struct EnemyShotList
{
    int size;
    Shot *first;
} EnemyShotList;

/*
* Cette fonction permet de créer une nouvelle liste
* Pré-condition : /
* Post-condition: renvoie l'adresse vers une nouvelle liste, vide
*/
EnemyShotList* newEnemyShotList();

/*
* Cette fonction permet d'insérer un nouvel élement au début de la liste
*/
void insertEnemyShotFront(EnemyShotList* ls, Shot shot);

/*
* Cette fonction permet de récupérer la taille de la liste
*/
int lengthEnemyShotList(EnemyShotList* ls);

/*
* Cette fonction permet de supprimer un élément de la liste doublement chaînée
*/
void deleteEnemyShot(EnemyShotList *ls, Shot* shot);

#endif