#include <GL/glut.h>
#include "view/end-game.h"
#include "view/game.h"
#include "view/navigation.h"
#include "view/start-menu.h"
#include <stdio.h>
#include <string.h>

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

int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(XWINDOWPOSITION, YWINDOWPOSITION);
    glutCreateWindow("Bike VS Cars");
    init();
    glutIdleFunc(vDisplayMain);//activation du callback

    glutMainLoop();
}

void init() {
    glutInitWindowSize(WIDTH_STARTMENU, HEIGHT_STARTMENU);
    glutInitWindowPosition(XWINDOWPOSITION_STARTMENU, YWINDOWPOSITION_STARTMENU);
    textureRoad = loadBMP_custom("./resources/road.bmp");
}

//TODO : bouger ca dans le fichier image-loader
GLuint loadBMP_custom(const char * imagepath) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3

    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file){printf("Image could not be opened\n"); return 0;}

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return 0;
    }

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    }
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    unsigned char data [imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);
    
    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
	GLuint textureID;
    
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 

	// Return the ID of the texture we just created
	return textureID;
}