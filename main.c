#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"

int main(int argc, char* argv[])
{
	Joueur j1;
	Joueur j2;
	Joueur j3;
	Joueur j4;
	char board[NB_CASE_BOARD] = {
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_', '_', '_', '_', '_',
		'_', '_'
	};
	// printf("%d", jet_des());
	init_game(j1, j2, j3, j4);
	affiche_player_stats(j2);
	return EXIT_SUCCESS;
}