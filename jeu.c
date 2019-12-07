#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jeu.h"


/* jet de dés de 1 à 6 */
int jet_des (void) {
	srand(time(NULL));
	return (rand() % (7 - 1) + 1);
}

char* int_couleur_to_char (int couleur) {
	switch (couleur)
	{
	case 0:
		return "rouge";
	case 1:
		return "bleu";
	case 2:
		return "jaune";
	
	default:
		return "vert";
	}
}

void affiche_player_stats(Joueur j) {
	printf("Joueur %s\nCouleur %s\n" \
	"Chevaux dans l'écurie : %d\n" \
	"Chevaux total réstant : %d" \
	, j.nom, int_couleur_to_char(j.couleur), \
	j.ecurie, j.nb_chevaux_restant);
}

void init_game(Joueur j1, Joueur j2, Joueur j3, Joueur j4) {
	// Joueur j1;
	// Joueur j2;
	// Joueur j3;
	// Joueur j4;
	
	printf("Joueur 1\nSaissez votre nom : ");
	fgets(j1.nom, MAX_NOM, stdin);
	if (strlen(j1.nom) == 1) {
		strcpy(j1.nom, "IA1");
	}
	j1.ecurie = 4;
	j1.nb_chevaux_restant = 4;
	j1.couleur = PLAYER1;
	printf("Joueur 2\nSaissez votre nom : ");
	fgets(j2.nom, MAX_NOM, stdin);
	if (strlen(j2.nom) == 1) {
		strcpy(j2.nom, "IA2");
	}
	j2.ecurie = 4;
	j2.nb_chevaux_restant = 4;
	j2.couleur = PLAYER2;
	printf("Joueur 3\nSaissez votre nom : ");
	fgets(j3.nom, MAX_NOM, stdin);
	if (strlen(j3.nom) == 1) {
		strcpy(j3.nom, "IA3");
	}
	j3.ecurie = 4;
	j3.nb_chevaux_restant = 4;
	j3.couleur = PLAYER3;
	printf("Joueur 4\nSaissez votre nom : ");
	fgets(j4.nom, MAX_NOM, stdin);
	if (strlen(j4.nom) == 1) {
		strcpy(j4.nom, "IA4");
	}
	j4.ecurie = 4;
	j4.nb_chevaux_restant = 4;
	j4.couleur = PLAYER4;
    // }

	printf("%s\n", j1.nom);
	printf("%s\n", j2.nom);
	printf("%s\n", j3.nom);
	printf("%s\n", j4.nom);

}