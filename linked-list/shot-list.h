/*
* Interface pour une liste chainée
* Mon implémentation de cette interface se trouve dans le fichier shotList.c
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./../structs/shot-struct.h"

typedef struct List
{
    int size;
    Shot *first;
} List;

/*
* Cette fonction permet de créer une nouvelle liste
* Pré-condition : /
* Post-condition: renvoie l'adresse vers une nouvelle liste, vide
*/
List* newList();

/*
* Cette fonction permet d'insérer un nouvel élement au début de la liste
* @Param {ls} liste doublement chaînée des tirs du vélo
* @Param {shot} tir du vélo
* Pré-condition : ls != NULL
* Post-condition: ls correspond à la liste initiale à laquelle un noeud a été ajouté au début, contenant l'élément nb; sa taille est incrémentée de 1
*/
void insertFront(List* ls, Shot* shot);

/*
* Cette fonction permet de récupérer la taille de la liste
* @Param {ls} liste doublement chainée dont on veut connaître la taille
* Pré-condition : ls != NULL
* Post-condition: renvoie le nombre d'éléments de ls
*/
int length(List* ls);

/*
* Cette fonction permet de supprimer un élément de la liste doublement chaînée
* @Param {ls} la liste dont un élément va être supprimé
* @Param {shot} l'élément qu'il faut supprimer de la liste
*/
void delete(List *ls, Shot* shot);
#endif