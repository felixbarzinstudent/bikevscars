<!--
         ____  ______ __ ______   _    _______    _________    ____  _____
        / __ )/  _/ //_// ____/  | |  / / ___/   / ____/   |  / __ \/ ___/
       / __  |/ // ,<  / __/     | | / /\__ \   / /   / /| | / /_/ /\__ \ 
      / /_/ // // /| |/ /___     | |/ /___/ /  / /___/ ___ |/ _, _/___/ / 
     /_____/___/_/ |_/_____/     |___//____/   \____/_/  |_/_/ |_|/____/  
                                                                          
 -->

# Welcome
Bienvenue dans le README de BIKE VS CARS

## Versions & libs

Jeu développé et testé sur Ubuntu Release 18.04
Visual studio code (écriture & debug) Release 1.41.0 
Librairies: OpenGL Release 3.1 
            OpenGL Utility Toolkit (GLUT)
            stb	Release 2.22

## Installation
Aller à la racine de la solution que vous avez clôné/téléchargé depuis github.
Il suffit ensuite d'entrer la commande make pour exécuter la compilation.

Exemple depuis mon terminal: felix@felix-VirtualBox: ~/Desktop/repos/learnglut/make

Cette commande permet la compilation de la solution grâce à une commande présente dans le makefile de cette solution.

Exécuter ensuite la commande ./batailleEtoiles pour lancer le jeu.

## Commande de compilation (voire makefile) 
gcc -Wall -std=c99 movement/bike-movement.o graphic/bike.o utils/calculus.o utils/text-tools.o utils/timer-tools.o view/start-menu.o view/game.o view/navigation.o view/end-game.o linked-list/shot-list.o graphic/enemy.o linked-list/enemy-list.o records/save.o linked-list/enemy-shot-list.o utils/image-loader.o graphic/obstacle.o main.o -o batailleEtoiles -lglut -lGLU -lGL -lm -ldl

## Makefile
Commande pour nettoyage des fichiers *.o et du launcher : make mrproper
Commande pour compilation : make

## Assets/Sprites
Royalty free license
