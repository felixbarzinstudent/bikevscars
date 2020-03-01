#include <GL/glut.h>
#include "view/end-game.h"
#include "view/game.h"
#include "view/start-menu.h"

/*
* définition des variables globales
* variables globales relatives aux numéros des fenêtres du programme
* Ces propriétés sont settées au moment ou la fenêtre est crée, il ne faut en aucun cas les 
* modifier ensuite
* 0 = fenetre menu départ
* 1 = fenetre de jeux
* 2 = fenêtre de fin de jeux
*/
int numWindows[2];

// UNUSED
void drawMenu() {
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-1.0, -0.5);
        glVertex2f(1.0, -0.5);
        glVertex2f(1.0, -1.0);
    glEnd();
}

int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    //Windows tittle is name of program

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //GLUT_DOUBLE pour activer le double buffering et GLUT_RGBA pour activer le mode couleur 32 bits
    
    /* fenêtre fin de partie */
    windowEndGame(numWindows);
    /* fenêtre du jeu */
    windowGame(numWindows);
    /* fenêtre du menu de départ */
    windowMenu(numWindows);
    glutMainLoop();

}