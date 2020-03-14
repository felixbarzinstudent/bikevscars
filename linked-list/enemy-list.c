#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./enemy-list.h"

EnemyList *newEnemyList()
{
    EnemyList *list = malloc(sizeof(list));
    list->first = NULL;
    list->size = 0;

    return list;
}

//PRE: ls != NULL
//POST: ls correspond à la liste initiale à laquelle un noeud a été ajouté au début, contenant l'élément nb; sa taille est incrémentée de 1
void insertEnemyFront(EnemyList *ls, Enemy enemy)
{
    Enemy *first = malloc(sizeof(Enemy));
    first->position.x = enemy.position.x;
    first->position.y = enemy.position.y;
    first->speed = enemy.speed;
    first->isAlive = enemy.isAlive;

    if(ls->first == NULL) { // si c'est la premiere insertion de la liste
        first->previous = NULL;
    } else {
        ls->first->previous = first;
    }
    first->next = ls->first;
    ls->first = first;

    ls->size += 1;
}

//PRE: ls != NULL
//POST: renvoie le number d'éléments de ls
int lengthEnemyList(EnemyList *ls)
{
    if (ls == NULL)
        exit(EXIT_FAILURE);
        
    if (ls->first == NULL)
        return 0; // Liste vide

    int counter = 0;
    Enemy *node = ls->first;

    if(node != NULL)
        counter++;

    while (node->next != NULL)
    {
        counter++;
        node = node->next;
    }

    return counter;
}

void deleteEnemy(EnemyList *ls, Enemy* enemy) {
    Enemy* current = ls->first;
    bool out = false;
    int counter = 0;
    while(!out && counter <= ls->size && current != NULL) {
        counter ++;
        if(enemy == current) {
            if(current->previous == NULL) { //si c'est le premier élément de la liste
                if(current->next == NULL) { //si c'est le seul élément de la liste
                    ls->first = NULL;
                    ls->size -= 1;
                    free(enemy);
                    out = true;
                } else {
                    current->next->previous = NULL;
                    ls->first = current->next;
                    ls->size -= 1;
                    free(enemy);
                    out = true;
                }
            } else {
                if(current->next == NULL) { //si c'est le dernier élément de la liste
                    if(current->previous != NULL)
                        current->previous->next = NULL;
                    ls->size -= 1;
                    free(enemy);
                    out = true;
                } else {
                    Enemy *tempCurrentNext = malloc(sizeof(Enemy));
                    Enemy *tempCurrentPrevious = malloc(sizeof(Enemy));
                    tempCurrentNext = current->next;
                    tempCurrentPrevious = current->previous;

                    current->previous->next = tempCurrentNext;
                    current->next->previous = tempCurrentPrevious;
                    ls->size -= 1;
                    free(enemy);
                    out = true;
                }
            }
        }
        current = current->next;

     }
}

void enemyListTest() {
    //printf("enemylis\n");
}