/*
* Interface pour une list chainée
* Mon implémentation de cette interface se trouve dans le fichier shot-list.c
*/

#ifndef ENEMYLIST_H
#define ENEMYLIST_H
#include "./../graphic/coordinate.h"

// typedef struct Shot Shot;
// struct Shot
// {
//     struct Coordinate position;
//     float speed;
//     Shot *next;
//     Shot *previous;
// };
typedef struct Enemy Enemy;
struct Enemy {
    struct Coordinate position;
    bool isAlive;
    float speed;
    Enemy *next;
    Enemy *previous;
};

typedef struct EnemyList
{
    int size;
    Enemy *first;
} EnemyList;

/*
* Cette fonction permet de créer une nouvelle liste
* Pré-condition : /
* Post-condition: renvoie l'adresse vers une nouvelle liste, vide
*/
EnemyList* newEnemyList();

/*
* Cette fonction permet d'insérer un nouvel élement au début de la liste
* @Param {list} list doublement chaînée contenant des ennemis
* @Param {enemy} nouvel ennemi
* Pré-condition : list != NULL
* Post-condition: list correspond à la list initiale à laquelle un noeud a été ajouté au début; sa taille est incrémentée de 1
*/
void insertEnemyFront(EnemyList* list, Enemy enemy);

/*
* Cette fonction permet de récupérer la taille de la liste
* @Param {list} liste doublement chainée dont on veut connaître la taille
* Pré-condition : list != NULL
* Post-condition: renvoie le nombre d'éléments de list
*/
int lengthEnemyList(EnemyList* list);

/*
* Cette fonction permet de supprimer un élément de la liste doublement chaînée
* @Param {list} la liste dont un élément va être supprimé
* @Param {enemy} l'élément qu'il faut supprimer de la liste
*/
void deleteEnemy(EnemyList *list, Enemy* enemy);
#endif