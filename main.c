#ifdef	__APPLE_CC__	
#include <GLUT/glut.h>	
#else	
#include <GL/glut.h>	
#endif
#include <stdio.h>
#include <string.h>
#include "utils/image-loader.h"
#include "view/end-game.h"
#include "view/game.h"
#include "view/navigation.h"
#include "view/start-menu.h"

GLuint textureRoad;
void init();
GLuint loadBMP_custom(const char * imagepath);
void vDisplayMain() {
    int id = getMainCurrentWindow();
    switch(id) {
        case 0:
            /* fenêtre du menu de départ */
            windowMenu(textureRoad);
        break;
        case 1:
            /* fenêtre du jeu */
            windowGame(textureRoad);
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

void resize() {
    glutReshapeWindow(WIDTH, HEIGHT);
}

int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(XWINDOWPOSITION, YWINDOWPOSITION);
    glutCreateWindow("Bike VS Cars");
    init();
    glutIdleFunc(vDisplayMain);//activation du callback
    glutReshapeFunc(resize);
    glutMainLoop();
}

void init() {
    glutInitWindowSize(WIDTH_STARTMENU, HEIGHT_STARTMENU);
    glutInitWindowPosition(XWINDOWPOSITION_STARTMENU, YWINDOWPOSITION_STARTMENU);
    textureRoad = loadBMP_custom("resources/road.bmp");
}