#include <stdio.h>
#include <stdlib.h>
#include "save.h"
/* déclaration des variables */

const int numberOfHighscoresToDisplay = 5; // Dans le menu, j'affiche les 5 meilleurs scores

/* déclaration des fonctions */
void getTop(int* tab);

void saveHighscores(int score) {
	int tab[numberOfHighscoresToDisplay + 1];
	FILE *fichier;
	
	fichier = fopen("records/highscores.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0; i < numberOfHighscoresToDisplay; i++) {
		    fscanf(fichier, "%d\n", tab+i);
        }

		fclose(fichier);

        for (int i = 0; i < numberOfHighscoresToDisplay; i++) { // vérifie que les données sont cohérentes
			if(tab[i] < 0 || tab[i] > 999)
			    tab[i] = 0;
		}

        tab[numberOfHighscoresToDisplay] = score;

        getTop(tab);
	}    

	fichier = fopen("records/highscores.txt","w");// Ouverture du fichier en écriture grâce à "w"
	
	if (fichier != NULL) { // Verifier que le fichier est ouvert
		// Ecriture
        for (int i = 0; i < numberOfHighscoresToDisplay; i++){
		    fprintf(fichier, "%d\n", tab[i]);
	    }
		// Fermeture du fichier
		fclose(fichier);
	}
}

/*
* Lire le fichier des meilleurs score et récupère les meilleus
* Compare les 5 meilleurs score au nouveau score et renvoi les 5 meilleurs
* Pré-condition : le fichier doit exister
*/
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

void saveCheckpoint(int points, int life, double seconds) {
	FILE *fichier;
	fichier = fopen("records/checkpoint.txt","w");// Ouverture du fichier en écriture grâce à "w"
	
	if (fichier != NULL) { // Verifier que le fichier est ouvert
		// Ecriture
		fprintf(fichier,"%i\n",points);
		fprintf(fichier,"%i\n",life);
		fprintf(fichier, "%i\n",(int) seconds);
		// Fermeture du fichier
		fclose(fichier);
	}
}

/*
* Pré-condition : un fichier de sauvegarde valide à sa premiere valeur et sa troisieme comprise entre 0 et 999 et sa deuxieme valeure compriuse entre 1 et 3
*/
int getLifeFromLastCheckpoint() {
	int tab[3];
	FILE *fichier;
	
	fichier = fopen("records/checkpoint.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0; i < 3; i++) {
		    fscanf(fichier, "%d\n", tab+i);
        }

		fclose(fichier);
	} else {
		exit(EXIT_FAILURE);
	}

	if(tab[1] <= 0)
		exit(EXIT_FAILURE);

	if( //si il y a une anomalie dans le fichier, renvoie la valeur par défaut pour la vie
		tab[0] < 0 
		|| tab[0] > 999
		|| tab[1] < 1 
		|| tab[1] > 3
		|| tab[2] < 0
		|| tab[2] > 999) {
        return 3;
		}

	return tab[1];
}

/*
* Pré-condition : un fichier de sauvegarde valide à sa premiere valeur et sa troisieme comprise entre 0 et 999 et sa deuxieme valeure compriuse entre 1 et 3
*/
int getPointsFromLastCheckpoint() {
	int tab[3];
	FILE *fichier;
	
	fichier = fopen("records/checkpoint.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0 ; i < 3; i++) {
		    fscanf(fichier, "%d\n", tab+i);
        }

		fclose(fichier);
	} 

	if((tab[0] / 10 * 10) % 10 != 0)
		exit(EXIT_FAILURE);

    if( //si il y a une anomalie dans le fichier, renvoie la valeur par défaut pour les points
		tab[0] < 0 
		|| tab[0] > 999
		|| tab[1] < 1 
		|| tab[1] > 3
		|| tab[2] < 0
		|| tab[2] > 999) {
        return 0;
		}

	return (tab[0] / 10 * 10);
}

int getTimeFromLastCheckpoint() {
	int tab[3];
	FILE *fichier;
	
	fichier = fopen("records/checkpoint.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0 ; i < 3; i++) {
		    fscanf(fichier, "%d\n", tab+i);
        }

		fclose(fichier);
	} 

    if( //si il y a une anomalie dans le fichier, renvoie la valeur par défaut pour les secondes
		tab[0] < 0 
		|| tab[0] > 999
		|| tab[1] < 1 
		|| tab[1] > 3
		|| tab[2] < 0
		|| tab[2] > 999) {
        return 0;
		}

	return tab[2];

}

void getHighscores(int highscores[], int number) {
	FILE *fichier;
	
	fichier = fopen("records/highscores.txt","r"); // Ouverture du fichier en lecture grâce à "r"
	if (fichier != NULL) {
		for (int i = 0 ; i < number; i++) {
		    fscanf(fichier, "%d\n", highscores+i);
        }

		fclose(fichier);

		for (int i = 0; i < number; i++) {
			if(highscores[i] < 0 || highscores[i] > 999)
			    highscores[i] = 0;
		}
	} 
}