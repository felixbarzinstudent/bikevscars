#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "./navigation.h"
#include "./start-menu.h"
#include "./../graphic/bike.h"
#include "./../utils/text-tools.h"
#include "./../records/save.h"

/* définititon des variables*/

/* définititon des fonctions */
float basey0 = 0.0;
float basey1 = 1.0;

int activeOption = 2;
int activeOptionMenuConfigurer = 1;

int activeMenu = 1;

void vClavier_startmenu(unsigned char key, int x, int y);
void vClavierSpecial_startmenu(int key, int x, int y);
void vDisplay_startmenu();
void displayStartMenu();
void displayStartMenuConfigurer();
void displayStartMenuRules();
void displayStartMenuRulesPoints();
void displayStartMenuHighscores();

GLuint texture;
void windowMenu(GLuint tex) {
    texture = tex;
    glutDisplayFunc(vDisplay_startmenu);
    glutSpecialFunc(vClavierSpecial_startmenu); // up and down
    glutKeyboardFunc(vClavier_startmenu); // enter
}

void vClavierSpecial_startmenu(int key, int x, int y) 
{
    if(activeMenu == 1) { // menu de base
        switch (key){
            case GLUT_KEY_UP:
                activeOption -= 1;
                if(activeOption < 1)
                    activeOption = 6;
                break;

            case GLUT_KEY_DOWN:
                activeOption += 1;
                if(activeOption > 6)
                    activeOption = 1;
                break;

            default:
            break;
        }
    } else if (activeMenu == 2) {
        switch (key){
            case GLUT_KEY_UP:
                activeOptionMenuConfigurer -= 1;
                if(activeOptionMenuConfigurer < 1)
                    activeOptionMenuConfigurer = 4;
                break;

            case GLUT_KEY_DOWN:
                activeOptionMenuConfigurer += 1;
                if(activeOptionMenuConfigurer > 4)
                    activeOptionMenuConfigurer = 1;
                break;

            default:
            break;
        }
    }
}

void vClavier_startmenu(unsigned char key, int x, int y) {
    if (activeMenu == 1) { // Menu de base
        if (key == 13) {
            if (activeOption == 1) {
                setMainCurrentWindow(1);
                _startMenuActiveOption = 1; // pour dire a la page de jeu qu'on veut reprendre au dernier checkpoint
            }
            else if (activeOption == 2)
                setMainCurrentWindow(1); // todo changer le hardcode 1 -> jeu
            else if (activeOption == 3)
                activeMenu = 2;
            else if (activeOption == 4)
                activeMenu = 3;
            else if (activeOption == 5)
                activeMenu = 5;
        }
    } else if (activeMenu == 2) { // Menu difficulté
        if (key == 13) {
            if (activeOptionMenuConfigurer == 1) {
                _difficulty = 1;
            } else if (activeOptionMenuConfigurer == 2) {
                _difficulty = 3;
            } else if (activeOptionMenuConfigurer == 3) {
                _difficulty = 10;
            } 

            activeMenu = 1;
        }
    } else if (activeMenu == 3) { // Menu regles page 1
        activeMenu = 4;
    } else if (activeMenu == 4) { // Menu regles page 2
        activeMenu = 1;
    } else if (activeMenu == 5) { // Menu highscores
        activeMenu = 1;
    }
}

void vDisplay_startmenu() {
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    basey0 += 0.00005;
    basey1 += 0.00005;
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(-0.9539f, basey0); glVertex2f(-1.005, -1); // en bas a gauche
            glTexCoord2f(-0.9539f, basey1); glVertex2f(-1.005, 1); // au dessus à gauche
            glTexCoord2f(0.0461f, basey1); glVertex2f(1.096, 1); // au dessus à droite
            glTexCoord2f(0.0461f, basey0); glVertex2f(1.096, -1); // en bas à droite
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    if(activeMenu == 1)
        displayStartMenu();
    if(activeMenu == 2)
        displayStartMenuConfigurer();
    if(activeMenu == 3)
        displayStartMenuRules();
    if(activeMenu == 4)
        displayStartMenuRulesPoints();
    if(activeMenu == 5)
        displayStartMenuHighscores();

    glutPostRedisplay();
    glutSwapBuffers(); 

}

void displayStartMenu() {
    char option1 [] = "Continuer la partie en cours";
    char option2 [] = "Commencer une nouvelle partie";
    char option3 [] = "Configurer le jeu";
    char option4 [] = "Lire les regles du jeu";
    char option5 [] = "Highscores";
    char option6 [] = "Quitter";
    char option7 [] = "Voulez-vous vraiment quitter ?";
    
    if(activeOption == 1 || activeOption == 6)
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 1, 1, 1);

    if(activeOption == 2 || activeOption == 6)
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 1, 1, 1);

    if(activeOption == 3 || activeOption == 6)
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 1, 1, 1);

    if(activeOption == 4 || activeOption == 6)
        writeOnWindow(-0.5, 0.2, option4, strlen(option4), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.2, option4, strlen(option4), 1, 1, 1);

    if(activeOption == 5 || activeOption == 6)
        writeOnWindow(-0.5, 0.1, option5, strlen(option5), 0, 0, 0);
    else
        writeOnWindow(-0.5, 0.1, option5, strlen(option5), 1, 1, 1);

    if(activeOption == 6)
        writeOnWindow(-0.5, 0.0, option7, strlen(option7), 1, 1, 1);
    else
        writeOnWindow(-0.5, 0.0, option6, strlen(option6), 1, 1, 1);
}

void displayStartMenuConfigurer() {
    char option1 [] = "Normal";
    char option2 [] = "Hardcore";
    char option3 [] = "Impossible";
    char option4 [] = "Retour";
    
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 0, 0, 0); 
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 0, 0, 0); 
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 0, 0, 0); 
        writeOnWindow(-0.5, 0.1, option4, strlen(option4), 0, 0, 0); 


    if(activeOptionMenuConfigurer == 1) {
        writeOnWindow(-0.5, 0.5, option1, strlen(option1), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 2) {
        writeOnWindow(-0.5, 0.4, option2, strlen(option2), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 3) {
        writeOnWindow(-0.5, 0.3, option3, strlen(option3), 1, 1, 1);
        return;
    }

    if(activeOptionMenuConfigurer == 4) {
        writeOnWindow(-0.5, 0.1, option4, strlen(option4), 1, 1, 1);
        return;
    }
}

void displayStartMenuRules() {
    char line1 [] = "En l'an 2021, dans un monde dystopique dans lequel les";
    char line2 [] = "voitures ce sont alliees pour detruire tous les vehicules";
    char line3 [] = "non-polluants, seul un velo ose resister envers et contre";
    char line4 [] = "tout pour mettre fin a cette oppression.";
    char line5 [] = "Guider le velo pour l'aider a resister, et detruire un max";
    char line6 [] = "de voiture ! Ces voitures sans scrupules vont essayer";
    char line7 [] = "d'ecraser les chats qui traversent la route.";
    char line8 [] = "Il faut les sauver ! ";
    char line8a [] = "Ces satanes voitures tirent sur tout ce qui bouge...";
    char line8b [] = "La police tentera de vous arreter en vous faisant obstacle";
    char line9 [] = "Commandes :";
    char line10 [] = "Fleches :";
    char line10a [] = "deplacer le velo";
    char line11 [] = "ESPACE :";
    char line11a [] = "tirer une onde sonore tueuse de voiture";
    char line12 [] = "F";
    char line12a [] = "utiliser des bulles de savon pour emprisonner";
    char line13 [] = "les voitures";
    char line14 [] = "ESC :";
    char line14a [] = "quitter la partie";
    char line14b [] = "Le jeu sauvegarde automatiquement a chaque checkpoint";
    char line15 [] = "Points [PRESS ENTER]";

    writeOnWindow(0.0, -0.95, line15, strlen(line15), 0, 0, 0); 
    writeOnWindow(-0.92, -0.30, line10, strlen(line10), 1, 1, 1); 
    writeOnWindow(-0.92, -0.40, line11, strlen(line11), 1, 1, 1); 
    writeOnWindow(-0.92, -0.50, line12, strlen(line12), 1, 1, 1); 
    writeOnWindow(-0.92, -0.70, line14, strlen(line14), 1, 1, 1); 

    writeOnWindow(-0.92, 0.94, line1, strlen(line1), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.92, 0.84, line2, strlen(line2), 0.98, 0.98, 0.98); 
    writeOnWindow(-0.92, 0.74, line3, strlen(line3), 0.97, 0.97, 0.97); 
    writeOnWindow(-0.92, 0.64, line4, strlen(line4), 0.96, 0.96, 0.96); 
    writeOnWindow(-0.92, 0.52, line5, strlen(line5), 0.95, 0.95, 0.95); 
    writeOnWindow(-0.92, 0.42, line6, strlen(line6), 0.96, 0.96, 0.96); 
    writeOnWindow(-0.92, 0.32, line7, strlen(line7), 0.97, 0.97, 0.97); 
    writeOnWindow(-0.92, 0.22, line8, strlen(line8), 0.98, 0.98, 0.98); 
    writeOnWindow(-0.92, 0.10, line8a, strlen(line8a), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.92, 0.00, line8b, strlen(line8b), 0.99, 0.99, 0.99); 
    
    writeOnWindow(-0.92, -0.15, line9, strlen(line9), 0.1, 0.1, 0.1); 
    writeOnWindow(-0.55, -0.30, line10a, strlen(line10a), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.55, -0.40, line11a, strlen(line11a), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.55, -0.50, line12a, strlen(line12a), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.55, -0.60, line13, strlen(line13), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.55, -0.70, line14a, strlen(line14a), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.92, -0.80, line14b, strlen(line14b), 0.99, 0.99, 0.99); 
    writeOnWindow(-0.55, -0.70, "", strlen(""), 0.59, 0.59, 0.59); 

}

void displayStartMenuRulesPoints() {
    char line1 [] = "Points :";
    char line2 [] = "Voiture detruite :";
    char line2a [] = "+1";
    char line3 [] = "Voiture detruite dans une bulle :";
    char line3a [] = "+2";
    char line4 [] = "Chat sauver :";
    char line4a [] = "+3";
    char line5 [] = "Chat tuer ou ecraser par une voiture :";
    char line5a [] = "-5";
    char line6 [] = "Retour au menu [PRESS ENTER]";

    writeOnWindow(-0.75, -0.85, line6, strlen(line6), 0, 0, 0); 
    writeOnWindow(-0.75, 0.30, line1, strlen(line1), 0.1, 0.1, 0.1); 
    writeOnWindow(-0.75, 0.10, line2, strlen(line2), 1, 1, 1); 
    writeOnWindow(0.49, 0.10, line2a, strlen(line2a), 1, 1, 1); 
    writeOnWindow(-0.75, 0.00, line3, strlen(line3), 1, 1, 1); 
    writeOnWindow(0.49, 0.00, line3a, strlen(line3a), 1, 1, 1); 
    writeOnWindow(-0.75, -0.10, line4, strlen(line4), 1, 1, 1); 
    writeOnWindow(0.49, -0.10, line4a, strlen(line4a), 1, 1, 1); 
    writeOnWindow(-0.75, -0.20, line5, strlen(line5), 1, 1, 1); 
    writeOnWindow(0.49, -0.20, line5a, strlen(line5a), 1, 1, 1); 
    writeOnWindow(-0.55, -0.70, "", strlen(""), 0.59, 0.59, 0.59); 
}

void displayStartMenuHighscores() {
    int highscores[5];
    getHighscores(highscores, 5);

    char line1[] = "HIGH-SCORES";
    char lineRetour[] = "Retour [PRESS ENTER]";
    writeOnWindow(-0.3, 0.3, line1, strlen(line1), 1, 1, 0.1);
    writeOnWindow(-0.4, -0.5, lineRetour, strlen(lineRetour), 0, 0, 0.0);

    char points[12];
    char endLinePoints[9] = " points\0";
    char rank[4];
    char endLineRank[3] = ".\0";
    float counter = 0; 
    for(int i = 0; i < 5; i++) {

        sprintf(points, "%i", highscores[i]);
        strcat(points, endLinePoints);

        sprintf(rank, "%i", (i+1));
        strcat(rank, endLineRank);

        writeOnWindow(-0.26, (0.1 - counter), rank, 4, 1, 1, 1);
        writeOnWindow(-0.17, (0.1 - counter), points, 12, 1, 1, 1);
        counter += 0.1;
    }
    writeOnWindow(-0.55, -0.70, "", strlen(""), 1, 1, 1);  
}