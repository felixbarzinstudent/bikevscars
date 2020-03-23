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
* @Param {ls} liste doublement chaînée contenant des tirs ennemis
* @Param {shot} tir a ajouter a la liste
* Pré-condition : list != NULL
* Post-condition: list correspond à la list initiale à laquelle un noeud a été ajouté au début; sa taille est incrémentée de 1
*/
void insertEnemyShotFront(EnemyShotList* ls, Shot* shot);

/*
* Cette fonction permet de récupérer la taille de la liste
* @Param {list} liste doublement chainée dont on veut connaître la taille
* Pré-condition : list != NULL
* Post-condition: renvoie le nombre d'éléments de list
*/
int lengthEnemyShotList(EnemyShotList* ls);

/*
* Cette fonction permet de supprimer un élément de la liste doublement chaînée
* @Param {list} la liste dont un élément va être supprimé
* @Param {enemy} l'élément qu'il faut supprimer de la liste
*/
void deleteEnemyShot(EnemyShotList *ls, Shot* shot);

#endif