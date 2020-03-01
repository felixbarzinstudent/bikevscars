#include <GL/glut.h>
#include "view/end-game.h"
#include "view/game.h"
#include "view/navigation.h"
#include "view/start-menu.h"

void vDisplayMain() {
    int id = getMainCurrentWindow();
    glutInitWindowSize(WIDTH_STARTMENU, HEIGHT_STARTMENU);
    glutInitWindowPosition(XWINDOWPOSITION_STARTMENU, YWINDOWPOSITION_STARTMENU);
    switch(id) {
        case 0:
            /* fenêtre du menu de départ */
            windowMenu();
        break;
        case 1:
            /* fenêtre du jeu */
            windowGame();
        break;
        case 2:
            /* fenêtre de fin de jeu */
            windowEndGame();
        break;
        default:
        break;
    }
    glutPostRedisplay();
    glutSwapBuffers(); 
}

int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //GLUT_DOUBLE pour activer le double buffering et GLUT_RGBA pour activer le mode couleur 32 bits
    
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(XWINDOWPOSITION, YWINDOWPOSITION);
    glutCreateWindow("Bike VS Cars");
    glutDisplayFunc(vDisplayMain);
    glutIdleFunc(vDisplayMain);//activation du callback

    glutMainLoop();
}