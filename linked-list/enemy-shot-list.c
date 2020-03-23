/*
* Implémentation d'une liste chainée
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./enemy-shot-list.h"
#include "./../graphic/coordinate.h"

EnemyShotList *newEnemyShotList()
{
    EnemyShotList *list = malloc(sizeof(list));
    list->first = NULL;
    list->size = 0;

    return list;
}

//PRE: ls != NULL
//POST: ls correspond à la liste initiale à laquelle un noeud a été ajouté au début, contenant l'élément nb; sa taille est incrémentée de 1
void insertEnemyShotFront(EnemyShotList *ls, Shot* shot)
{
    Shot *first = malloc(sizeof(Shot));
    first->position.x = shot->position.x;
    first->position.y = shot->position.y;
    first->position.z = 0;
    first->type = 1;
    
    first->speed = shot->speed;
    
    if(ls->first == NULL) { // si c'est la premiere insertion de la liste
        first->previous = NULL;
        first->next = NULL;
        ls->first = first;
    } else {
        Shot* lsFirstTemp = malloc(sizeof(Shot));
        lsFirstTemp = ls->first;
        ls->first->previous = first;
        first->next = lsFirstTemp;
        first->previous = NULL;
        ls->first = first;
    }

    ls->size += 1;
}

//PRE: ls != NULL
//POST: renvoie le number d'éléments de ls
int lengthEnemyShotList(EnemyShotList *ls)
{
    if (ls == NULL)
        exit(EXIT_FAILURE);
        
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

void deleteEnemyShot(EnemyShotList *ls, Shot* shot) {
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

                    if (current->previous->speed > 0 && current->previous != NULL && current->previous->next != NULL)
                        current->previous->next = tempCurrentNext;
                    else
                        current->previous = tempCurrentNext; // TODO : PAS SUR DU TOUT DE CA

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