#include "jeu.h"

/* jet de dés de 1 à 6 */
int jet_des() {
	srand(time(NULL));
	return (rand() % 6 + 1);
}

/*nettoie le terminal*/
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

/*recupere les input dynamiquement*/
char* get_input() {
	char* input = (char*)malloc(sizeof(char));
	int c;
	int acc = 0;
	if (input == NULL) {
		printf("Erreur d'allocation memoire\n");
		exit(EXIT_FAILURE);
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
	while (scanf("%d", &n) != 1 || !(n >= 2 && n <= 4) == 1) {
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

void game() {
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
joueur_t* init_joueur(int couleur, short i, int* array_des) {
	joueur_t* j = (joueur_t*)malloc(sizeof(joueur_t));
	int array_couleur[4] = { ROUGE, BLEU, VERT, JAUNE };
	char Kcouleur[4][8] = { {KRED}, {KBLU}, {KGRN}, {KYEL} };
	char* name_cheval = (char*)malloc(sizeof(char) * 3);
	name_cheval[0] = 'C';
	name_cheval[2] = '\0';
	printf("Nom du joueur %d : ", i);
	//char* tmp = get_input();
	j->num_j = i;
	j->nom = get_input();
	//j->nom = (char*)malloc(sizeof(char) * strlen(tmp) + 1);
	//strcpy(j->nom, tmp);
	j->ecurie = 4;
	j->couleur = couleur;
	j->jet_des = jet_des();
	array_des[i] = j->jet_des;
	for (int i = 0; i < 4; i++) {
		name_cheval[1] = (i+1) + '0';
		init_chevaux(array_couleur[i], i + 1, Kcouleur[i],  name_cheval);
	}
	desalloc_ptr(name_cheval);
	return j;
}

chevaux_t init_chevaux(int couleur, int numero, char* Kcouleur, char* name_case) {
	chevaux_t chevaux;
	chevaux.couleur = couleur;
	chevaux.numero = numero;
	chevaux.cli_couleur = (char*)malloc(sizeof(char) * strlen(Kcouleur));
	chevaux.name_case = (char*)malloc(sizeof(char) * strlen(name_case));
	strcpy(chevaux.cli_couleur, Kcouleur);
	strcpy(chevaux.name_case, name_case);
	return chevaux;
}

int start_choice() {
	int n;
	printf("Bienvenue dans le jeu des petits chevaux\n"\
		"          [1] Nouvelle partie\n"\
		"          [2] Charger une partie\n"
		"          [3] Quitter\n");
	while (scanf("%d", &n) != 1 || !(n >= 1 && n <= 3)) {
		while (getchar() != '\n');
		printf("Choix non valide\nFaites un choix :\n"\
			"          [1] Nouvelle partie\n"\
			"          [2] Charger une partie\n"
			"          [3] Quitter\n");
	}
	return n;
}

int ingame_choice() {
	int n;
	printf("Faites un choix :\n"\
		"          [1] Jeter les des\n"\
		"          [2] Sauvegarder la partie");
	while (scanf("%d", &n) != 1 || !(n >= 1 && n <= 2) == 1) {
		while (getchar() != '\n');
		printf("Choix non valide\nFaites un choix :\n"\
			"          [1] Jeter les des\n"\
			"          [2] Sauvegarder la partie");
	}
	return n;
}

/* libere l'espace alloue d'un pointeur */
void desalloc_ptr(void* ptr) {
	if (ptr != NULL) {
		free(ptr);
	}
}

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, int tour) {
	plateau_t p;
	char* c = (char*)malloc(sizeof(char) * 2);
	c[1] = '\0';
	for (int i = 0; i < LEN_BOARD; i++) {
		p.board[i] = init_chevaux(VIDE, -1, KNRM, "#");
	}
	p.board[LEN_BOARD-1] = init_chevaux(BOARD_END, -1, "", "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		c[0] = (i + 1) + '0';
		p.rouge_f[i] = init_chevaux(VIDE, -1, KNRM, c);
	}
	p.rouge_f[LEN_BOARD_FINAL-1] = init_chevaux(BOARD_END, -1, "", "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		c[0] = (i + 1) + '0';
		p.bleu_f[i] = init_chevaux(ROUGE, -1, KRED, c);
	}
	p.bleu_f[LEN_BOARD_FINAL-1] = init_chevaux(BOARD_END, -1, "", "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		c[0] = (i + 1) + '0';
		p.jaune_f[i] = init_chevaux(VERT, -1, KYEL, c);
	}
	p.jaune_f[LEN_BOARD_FINAL - 1] = init_chevaux(BOARD_END, -1, "", "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		c[0] = (i + 1) + '0';
		p.vert_f[i] = init_chevaux(BLEU, -1, KNRM, c);
	}
	p.vert_f[LEN_BOARD_FINAL - 1] = init_chevaux(BOARD_END, -1, "", "");
	desalloc_ptr(c);
	/*plateau_t p;
	p.board = (char**)malloc(sizeof(char*) * ROWS);
	for (int i = 0; i < ROWS; i++) {
		p.board[i] = (char*)malloc(sizeof(char) * COLS);
	}
	p.board[0] = "###";
	p.board[1] = "#1#";
	p.board[2] = "#2#";
	p.board[3] = "#3#";
	p.board[4] = "#4#";
	p.board[5] = "#5#";
	p.board[6] = "#######6#######";
	p.board[7] = "#123456X654321#";
	p.board[8] = "#######6#######";
	p.board[9] = "#5#";
	p.board[10] = "#4#";
	p.board[11] = "#3#";
	p.board[12] = "#2#";
	p.board[13] = "#1#";
	p.board[14] = "###";
	p.board[15] = '\0';*/
	/*p.board = (char*)malloc(sizeof(char) * MAX + 1);
	for (int i = 0; i < MAX; i++) {
		p.board[i] = '#';
	}
	p.board[MAX] = '\0';*/
	p.nb_joueurs = nb_joueurs;
	p.tour = tour;
	return p;
}


/* verifie s'il y a un gagnant*/
/*int is_win(plateau_t p) {
	int convert = char_to_int(p.board[LEN_BOARD-1]);
	return convert != VIDE ? convert : 0;
}

// regarde si une case est vide
int is_vide(plateau_t p, int _case) {
	return char_to_int(p.board[_case]) == VIDE;
}

// regarde s'il y a un cheval a une 
// case donne si oui, renvoie sa couleur
int check_cheval(plateau_t p, int _case) {
	return char_to_int(p.board[_case]);
}

// 


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
}*/
void modif_case(plateau_t p, joueur_t* j, int i) {
	strcpy(p.board[i].name_case, j->chevaux[i].name_case);
}


/* affiche le plateau de jeu */
void affiche_plateau(plateau_t p) {
	/*int i = 0;
	size_t len_prev;
	while (p.board[i] != '\0') {
		len_prev = strlen(p.board[i]);
		if (len_prev == 3) {
			printf("            ");
		}
		for (int j = 0; p.board[i][j] != '\0'; j++) {
			if (i < 6 && i > 0 && j == 1) {
				printf("%s%c %s", KRED, p.board[i][j], KNRM);
			}
			else if (i == 0 && j == 2) {
				printf("%s%c %s", KRED, p.board[i][j], KNRM);
			}
			else if (i == 6) {
				if (j == 7) {
					printf("%s%c %s", KRED, p.board[i][j], KNRM);
				}
				else if (j == 0) {
					printf("%s%c %s", KBLU, p.board[i][j], KNRM);
				}
				else {
					printf("%c ", p.board[i][j]);
				}
			}
			else if (i == 7) {
				if (j > 0 && j < 7) {
					printf("%s%c %s", KBLU, p.board[i][j], KNRM);
				}
				else if (j > 7 && j < 14) {
					printf("%s%c %s", KGRN, p.board[i][j], KNRM);
				}
				else {
					printf("%c ", p.board[i][j]);
				}
			}
			else if (i == 8 && j == 14) {
				printf("%s%c %s", KGRN, p.board[i][j], KNRM);
			}
			else if (i == 8 && j == 7) {
				printf("%s%c %s", KYEL, p.board[i][j], KNRM);
			}
			else if (i > 8 && i < 14 && j == 1) {
				printf("%s%c %s", KYEL, p.board[i][j], KNRM);
			}
			else if (i == 14 && j == 0) {
				printf("%s%c %s", KYEL, p.board[i][j], KNRM);
			}
			else {
				printf("%c ", p.board[i][j]);
			}
		}
		printf("\n");
		i++;
	}*/
	chevaux_t c_idx;
	int acc = 0;
	for (int i = 0; p.board[i].couleur != BOARD_END; i++) {
		c_idx = p.board[i];
		
		if (i % 3 == 0) {
			printf("\n");
		}
		//if (( i >= 1 && i <= 5) || )
		if (strcmp("C1", p.board[i].name_case) == 0) {
			printf("%s%s%s  ", KRED, c_idx.name_case, KNRM);
		}
		else {
			printf("%s  ", c_idx.name_case);
		}
	}
	/*for (int i = 0; p.rouge_f[i].couleur != BOARD_END; i++) {
		c_idx = p.rouge_f[i];
		printf("%s\n", c_idx.name_case);
	}*/
}

void save(plateau_t board, char* path) {}

plateau_t load(char* path) {}
