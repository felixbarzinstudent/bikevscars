/*
* Implémentation d'une liste chainée
*/

#include <stdbool.h>
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
    Shot *first = malloc(sizeof(Shot));
    first->position.x = shot.position.x;
    first->position.y = shot.position.y;
    first->speed = shot.speed;
    
    if(ls->first == NULL) { // si c'est la premiere insertion de la liste
        printf("1\n");
        first->previous = NULL;
    } else {
        printf("2\n");
        ls->first->previous = first;
    }
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

void delete(List *ls, Shot* shot) {
    Shot* current = ls->first;
    bool out = false;
    int counter = 0;
    while(!out && counter <= ls->size && current != NULL) {
        counter ++;
        if(shot == current) {
            if(current->previous == NULL) { //si c'est le premier élément de la liste
                if(current->next == NULL) { //si c'est le seul élément de la liste
                    ls->first = NULL;
                    ls->size -= 1;
                    free(shot);
                    out = true;
                } else {
                    current->next->previous = NULL;
                    ls->first = current->next;
                    ls->size -= 1;
                    free(shot);
                    out = true;
                }
            } else {
                if(current->next == NULL) { //si c'est le dernier élément de la liste
                    current->previous->next = NULL;
                    ls->size -= 1;
                    free(shot);
                    out = true;
                } else {
                    Shot *tempCurrentNext = malloc(sizeof(Shot));
                    Shot *tempCurrentPrevious = malloc(sizeof(Shot));
                    tempCurrentNext = current->next;
                    tempCurrentPrevious = current->previous;

                    current->previous->next = tempCurrentNext;
                    current->next->previous = tempCurrentPrevious;
                    ls->size -= 1;
                    free(shot);
                    out = true;
                }
            }
        }
        current = current->next;

     }
}