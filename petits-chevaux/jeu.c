#include "jeu.h"

/* jet de dés de 1 à 6 */
int jet_des() {
	srand(time(NULL));
	return (rand() % (7 - 1) + 1);
}

/* convertit la couleur int en char */
char* int_couleur_to_char(int couleur) {
	switch (couleur) {
	case 0:
		return "rouge";
	case 1:
		return "bleu";
	case 2:
		return "vert";
	case 3:
		return "jaune";
	case 4:
		return "vide";
	default:
		break;
	}
	return "couleur non definie";
}

/* obtient le nombre de joueurs pour la partie */
int get_nb_joueurs() {
	int n;
	printf("Combien y a t-il de joueurs ? ");
	scanf(" %d", &n);
	fflush(stdin);
	if (isdigit(n) && n >= 2 && n <= 4) {
		return n;
	}
	else {
		printf("Reessayer, 2 a 4 joueurs max\n");
		return get_nb_joueurs();
	}
}

void init_game() {
	int nb_joueurs = get_nb_joueurs();
	joueur_t* j1 = init_joueur(ROUGE, 1);
	joueur_t* j2 = init_joueur(BLEU, 2);
	joueur_t* j3 = NULL;
	joueur_t* j4 = NULL;
	
	if (nb_joueurs == 3) {
		j3 = init_joueur(VERT, 3);
	}
	else if (nb_joueurs == 4) {
		j3 = init_joueur(VERT, 3);
		j4 = init_joueur(JAUNE, 4);
	}
	affiche_etat_joueur(j1);
	affiche_etat_joueur(j2);
	affiche_etat_joueur(j3);
	affiche_etat_joueur(j4);
}

/*affiche l'etat du joueur (nom, ecurie, couleur)*/
void affiche_etat_joueur(joueur_t* j) {
	printf("Joueur %s\n", j->nom);
	printf("Il y a %d chevaux dans votre ecurie\n", j->ecurie);
	printf("Couleur %s\n", char_to_couleur(int_couleur_to_char(j->couleur)));
}

/* initialise un joueur */
joueur_t* init_joueur(int couleur, int i) {
	char nom_joueur[MAX_NOM];
	joueur_t* j = (joueur_t*)malloc(sizeof(joueur_t));
	printf("Nom du joueur %d : ", i);
	scanf(" %[^\n]", nom_joueur);
	fflush(stdin); /* clean buffer */
	strcpy(j->nom, nom_joueur);
	j->ecurie = 4;
	j->couleur = couleur;
	return j;
}

/*convertit char vers couleur*/
int char_to_couleur(char* s) {
	if (strcmp(s, "rouge") == 0) {
		return ROUGE;
	}
	else if (strcmp(s, "vert") == 0) {
		return VERT;
	}
	else if (strcmp(s, "bleu") == 0) {
		return BLEU;
	}
	else if (strcmp(s, "jaune") == 0) {
		return JAUNE;
	}
	return VIDE;
}

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, int tour) {
	plateau_t p;
	cheval_t board[MAX_BOARD];
	for (int i = 0; i < MAX_BOARD; i++) {
		p.board[i] = init_cheval(VIDE);
	}
	p.nb_joueurs = nb_joueurs;
	p.tour = tour;
	return p;
}

/* initialise un cheval*/
cheval_t init_cheval(int couleur) {
	cheval_t c = { .couleur = couleur };
	return c;
}

/* verifie s'il y a un gagnant*/
int is_win(plateau_t p) {
	int convert = char_to_couleur(p.board[80]);
	if (convert != VIDE) {
		return convert;
	}
	return 0;
}

int check_cheval(plateau_t p, int _case) {
	return char_to_couleur(p.board[_case]);
}


/* affiche le plateau de jeu */
void affiche_plateau(plateau_t board) {}