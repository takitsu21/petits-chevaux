#include "jeu.h"

/* jet de dés de 1 à 6 */
int jet_des() {
	srand(time(NULL));
	return (rand() % (7 - 1) + 1);
}

/* convertit la couleur int en char */
char int_couleur_to_char(int couleur) {
	switch (couleur) {
	case 0:
		return 'r';
	case 1:
		return 'b';
	case 2:
		return 'v';
	case 3:
		return 'j';
	case 4:
		return '.';
	default:
		break;
	}
	return 'e';
}

/* convertit une couleur char en entier*/
int char_to_int(char c) {
	switch (c)
	{
	case 'r':
		return ROUGE;
	case 'b':
		return BLEU;
	case 'v':
		return VERT;
	case 'j':
		return JAUNE;
	default:
		break;
	}
	return VIDE;
}

/* obtient le nombre de joueurs pour la partie */
int get_nb_joueurs() {
	int n;
	printf("Combien y a t-il de joueurs ? ");
	scanf(" %d", &n);
	fflush(stdin);
	while (n > 4 || n < 2) {
		printf("Reessayer, 2 a 4 joueurs max : ");
		scanf(" %d", &n);
		fflush(stdin);
	}
	return n;
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
	if (j3 != NULL) {
		affiche_etat_joueur(j3);
	}
	if (j4 != NULL) {
		affiche_etat_joueur(j4);
	}
}

/*affiche l'etat du joueur (nom, ecurie, couleur)*/
void affiche_etat_joueur(joueur_t* j) {
	printf("Joueur %s\n", j->nom);
	printf("Il y a %d chevaux dans votre ecurie\n", j->ecurie);
	printf("Couleur %s\n", int_couleur_to_char(j->couleur));
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

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, int tour) {
	plateau_t p;
	char board[MAX_BOARD];
	int i = 0;
	for (; i < MAX_BOARD; i++) {
		p.board[i] = '.';
	}
	p.nb_joueurs = nb_joueurs;
	p.tour = tour;
	return p;
}

/* verifie s'il y a un gagnant*/
int is_win(plateau_t p) {
	int convert = char_to_int(p.board[MAX_BOARD-1]);
	if (convert != VIDE) {
		return convert;
	}
	return 0;
}

/* regarde si une case est vide*/
int is_vide(plateau_t p, int _case) {
	return char_to_int(p.board[_case]) == VIDE;
}

/* regarde s'il y a un cheval a une 
case donne si oui, renvoie sa couleur*/
int check_cheval(plateau_t p, int _case) {
	return char_to_int(p.board[_case]);
}

/* modifie la case du plateau*/
void modif_case(plateau_t p, int _case, joueur_t j) {
	p.board[_case] = int_couleur_to_char(j.couleur);
}

/* affiche le plateau de jeu */
void affiche_plateau(plateau_t p) {}