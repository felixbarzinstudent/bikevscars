/*
* Implémentation d'une liste chainée
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./shot-list.h"
#include "./../graphic/character.h"

List *newList()
{
    List *list = malloc(sizeof(list));
    list->first = NULL;
    list->size = 0;

    return list;
}

//PRE: ls != NULL
//POST: ls correspond à la liste initiale à laquelle un noeud a été ajouté au début, contenant l'élément nb; sa taille est incrémentée de 1
void insertFront(List *ls, Shot shot)
{
    Shot *first = malloc(sizeof(first));
    first->position.x = shot.position.x;
    first->position.y = shot.position.y;
    first->speed = shot.speed;

    first->next = ls->first;
    ls->first = first;
    ls->size += 1;
}

//PRE: ls != NULL
//POST: renvoie le number d'éléments de ls
int length(List *ls)
{
    if (ls->first == NULL)
        return 0; // Liste vide

    int counter = 0;
    Shot *node = ls->first;

    if(node != NULL)
        counter++;

    while (node->next != NULL)
    {
        counter++;
        node = node->next;
    }

    return counter;
}