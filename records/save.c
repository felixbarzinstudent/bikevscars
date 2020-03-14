#include <stdio.h>
#include <stdlib.h>
#include "./save.h"

const int numberOfHighscoresToDisplay = 5;

void saveHighscores(int score) {
	int tab[numberOfHighscoresToDisplay + 1];
	FILE *fichier;
	
	fichier = fopen("/home/felix/Desktop/repos/learnglut/records/highscores.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0 ; i < numberOfHighscoresToDisplay; i++) {
		    fscanf(fichier,"%d\n",tab+i);
        }

		fclose(fichier);
        tab[numberOfHighscoresToDisplay] = score;

        getTop(tab);
	}    

	fichier = fopen("/home/felix/Desktop/repos/learnglut/records/highscores.txt","w");// Ouverture du fichier en écriture grâce à "w"
	
	if (fichier != NULL) { // Verifier que le fichier est ouvert
		// Ecriture
        for (int i = 0; i < numberOfHighscoresToDisplay; i++){
		    fprintf(fichier,"%d\n",tab[i]);
	    }
		// Fermeture du fichier
		fclose(fichier);
	}
}

// regarde les 5 meilleur score et le nouveau score, renvoi les 5 meilleures parmis les 6
void getTop(int* tab) {
    for (int i = 0; i < numberOfHighscoresToDisplay + 1; i ++) {
        for (int j = 0; j < numberOfHighscoresToDisplay + 1 ; j++) {
            if(tab[j] < tab[i]) {
                int tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

void saveCheckpoint(int points, int life) {
	FILE *fichier;
	fichier = fopen("/home/felix/Desktop/repos/learnglut/records/checkpoint.txt","w");// Ouverture du fichier en écriture grâce à "w"
	
	if (fichier != NULL) { // Verifier que le fichier est ouvert
		// Ecriture
		fprintf(fichier,"%i\n",points);
		fprintf(fichier,"%i\n",life);
		// Fermeture du fichier
		fclose(fichier);
	}
}