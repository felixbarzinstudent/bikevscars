#ifdef	__APPLE_CC__	
#include <GLUT/glut.h>	
#else	
#include <GL/glut.h>	
#endif

/*
* Ce loader permet de charger une image grâce à la librairie 'stb'
* @Param {path} chemin relatif vers l'image
*/
GLuint loadTexture(char path[]);
/*
* Ce loader permet de charger une image sans utiliser une librairie
* @Param {imagepath} chemin relatif vers l'image
*/
GLuint loadBMP_custom(const char * imagepath);