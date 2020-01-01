#include "jeu.h"

/* jet de dés de 1 à 6 */
int jet_des() {
	srand(time(NULL));
	return (rand() % 6 + 1);
}

void cls() {
	system("cls");
}

/* convertit la couleur int en char */
char int_couleur_to_char(int couleur) {
	switch (couleur) {
	case ROUGE:
		return 'r';
	case BLEU:
		return 'b';
	case VERT:
		return 'v';
	case JAUNE:
		return 'j';
	case VIDE:
		return '.';
	default:
		break;
	}
	return 'e'; // erreur
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

/* Recuperer les input dynamiquement*/
char* get_input() {
	char* input = (char*)malloc(sizeof(char));
	int c;
	int acc = 0;
	if (input == NULL) {
		printf("Erreur d'allocation memoire\n");
		exit(1);
	}
	c = getchar();
	input = realloc(input, sizeof(char) * acc + 1);
	input[acc++] = c;
	while ((c = getchar()) != '\n' && c != EOF) {
		input = realloc(input, sizeof(char) * acc + 1);
		input[acc] = c;
		acc++;
	}
	input[acc] = '\0';
	return input;
}

/* obtient le nombre de joueurs pour la partie */
int get_nb_joueurs() {
	int n;
	printf("Combien y a t-il de joueurs ? ");
	while (scanf("%d", &n) != 1) {
		while (getchar() != '\n');
		printf("Reessayer, 2 a 4 joueurs max : ");
	}
	return n;
}

char* char_to_string(char c) {
	switch (c)
	{
	case 'r':
		return "rouge";
	case 'v':
		return "vert";
	case 'j':
		return "jaune";
	case 'b':
		return "bleu";
	default:
		break;
	}
	return "vide";
}

void init_game() {
	int nb_joueurs = get_nb_joueurs();
	int* array_des = (int*)malloc(sizeof(int) * nb_joueurs);
	joueur_t* j1 = init_joueur(ROUGE, 1, array_des);
	joueur_t* j2 = init_joueur(BLEU, 2, array_des);
	joueur_t* j3 = NULL;
	joueur_t* j4 = NULL;
	plateau_t p;
	if (nb_joueurs == 3) {
		j3 = init_joueur(VERT, 3, array_des);
	}
	else if (nb_joueurs == 4) {
		j3 = init_joueur(VERT, 3, array_des);
		j4 = init_joueur(JAUNE, 4, array_des);
	}
	affiche_etat_joueur(j1);
	affiche_etat_joueur(j2);
	if (j3 != NULL) {
		affiche_etat_joueur(j3);
	}
	else {
		// TODO : faire spawn un pnj
	}
	if (j4 != NULL) {
		affiche_etat_joueur(j4 );
	}
	else {
		// TODO : faire spawn un pnj
	}
	p = init_plateau(nb_joueurs, check_who_start(array_des, nb_joueurs));
	printf("Joueur %c commence\n", int_couleur_to_char(p.tour));
	affiche_plateau(p);
	//printf("board = %s \n strlen(p.board) = %d\n", p.board, strlen(p.board));
	//cls();
	system("pause");
}

int check_who_start(int* des, int nb_joueurs) {
	int max = 0;
	int idx = 0;
	for (int i = 0; i < nb_joueurs; i++) {
		if (des[i] > max) {
			max = des[i];
			idx = i;
		}
	}
	return idx;
}

/*affiche l'etat du joueur (nom, ecurie, couleur)*/
void affiche_etat_joueur(joueur_t* j) {
	printf("Joueur %s\n", j->nom);
	printf("Il y a %d chevaux dans votre ecurie\n", j->ecurie);
	printf("Couleur %c\n", int_couleur_to_char(j->couleur));
}

/* initialise un joueur */
joueur_t* init_joueur(int couleur, int i, int* array_des) {
	joueur_t* j = (joueur_t*)malloc(sizeof(joueur_t));
	printf("Nom du joueur %d : ", i);
	char* tmp = get_input();
	j->nom = (char*)malloc(sizeof(char) * strlen(tmp) + 1);
	strcpy(j->nom, tmp);
	j->ecurie = 4;
	j->couleur = couleur;
	j->jet_des = jet_des();
	array_des[i] = j->jet_des;
	return j;
}

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, int tour) {
	plateau_t p;
	char tmp[] = "####1##2##3##4##5########6########123456X654321########6########5##4##3##2##1####";
	size_t len_board = strlen(tmp);
	p.board = malloc(sizeof(char) * len_board);
	strcpy(p.board, tmp);
	//p.board = "####1##2##3##4##5########6########123456X654321########6########5##4##3##2##1####";
	p.nb_joueurs = nb_joueurs;//
	p.tour = tour;
	return p;
}

/* verifie s'il y a un gagnant*/
int is_win(plateau_t p) {
	int convert = char_to_int(p.board[MAX_BOARD-1]);
	return convert != VIDE ? convert : 0;
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

void tour_suivant(plateau_t p) {
	p.tour += 1 % p.nb_joueurs;
}

void manger_cheval(plateau_t p, joueur_t* j, joueur_t* j_manger, int _case) {
	p.board[_case] = int_couleur_to_char(j->couleur);
	j_manger->ecurie += 1;
}

int match_case_start(int couleur) {
	switch (couleur)
	{
	case VERT:
		return V_START;
	case JAUNE:
		return J_START;
	case BLEU:
		return B_START;
	case ROUGE:
		return R_START;
	default:
		break;
	}
	return VIDE;
}

void sortie_ecurie(plateau_t p, joueur_t* j) {
	if (j->ecurie > 0) {
		int _case = match_case_start(j->couleur);
		p.board[_case] = int_couleur_to_char(j->couleur);
		j->ecurie -= 1;
	}
	else {
		printf("Impossible de sortir un cheval car %s n'a plus de chevaux dans son ecurie", j->nom);
	}
}


/* affiche le plateau de jeu */
void affiche_plateau(plateau_t p) {
	int i = 0;
	int acc_color = 0;
	int is_open = 0;
	/*char* color_changer[] = { "\x1B[31m",
							  "\x1B[33m",
							  "\x1B[32m", "\x1B[34m", "\x1B[0m" };*/
	while (p.board[i] != '\0') {
		/*if (!is_open && isdigit(p.board[i]) && p.board[i] - '0' == 1) {
			is_open = 1;
			printf("%s", KRED);
		}
		if (is_open && isdigit(p.board[i]) && p.board[i] - '0' == 6) {
			printf("%c ", p.board[i]);
			is_open = 0;
			acc_color++;
		}*/
		if (i == 18 || i == 33 || i == 48) {
			printf("\n");
		}
		else if (i % 3 == 0 && (i < 18 || i >= 63)) {
			printf("\n");
			printf("            ");
		}
		if (i == 2) {
			printf("%s%c ", KRED, p.board[i]);
		}
		else if (i == 78) {
			printf("%s%c ", KGRN, p.board[i]);
		}
		else if (i == 62) {
			printf("%s%c ", KYEL, p.board[i]);
		}
		else if (i == 18) {
			printf("%s%c ", KBLU, p.board[i]);
		}
		else {
			printf("%s%c ", KNRM, p.board[i]);
		}
		i++;
	}
	printf("\n");
	//printf("%s", board);
	//printf("%d", isalpha(board));
	//printf("%s", board);

}

void save(plateau_t board, char* path) {}

plateau_t load(char* path) {}

void game() {}