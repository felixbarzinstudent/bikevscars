#include <GL/glut.h>
#include <stdio.h>

unsigned char* loadBMP_custom(const char * imagepath) {
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
gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, data);
	// Return the ID of the texture we just created
	return data;
}