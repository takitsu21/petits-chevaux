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
	//printf("Joueur %c commence\n", int_couleur_to_char(p.tour));
	cls();
	int tmp;
	//p.board[0] = j1->chevaux[0];
	//affiche_plateau(p);
	for (int i = 0; i < 56; i++) {
		tmp = i;
		p.board[i] = j2->chevaux[0];
		printf("%s", KNRM);
		affiche_plateau(p);
		p.board[tmp].name_case = KNRM "#  ";
		Sleep(250);
		cls();
	}
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
	/*printf("Joueur %s\n", j->nom);
	printf("Il y a %d chevaux dans votre ecurie\n", j->ecurie);
	printf("Couleur %c\n", int_couleur_to_char(j->couleur));*/
}

/* initialise un joueur */
joueur_t* init_joueur(int couleur, short i, int* array_des) {
	joueur_t* j = (joueur_t*)malloc(sizeof(joueur_t));
	char num_chevaux[4][4] = { {"C1 "}, {"C2 "}, {"C3 "}, {"C4 "} };
	printf("Nom du joueur %d : ", i);
	j->num_j = i;
	j->nom = get_input();
	j->ecurie = 4;
	j->couleur = couleur;
	j->jet_des = jet_des();
	array_des[i] = j->jet_des;
	for (int i = 0; i < 4; i++) {
		j->chevaux[i] = init_chevaux(couleur, i + 1, num_chevaux[i]);
	}
	return j;
}

chevaux_t init_chevaux(int couleur, int numero, char* name_case) {
	chevaux_t chevaux;
	chevaux.couleur = couleur;
	chevaux.numero = numero;
	chevaux.position = -1;
	chevaux.name_case = (char*)malloc(sizeof(char) * strlen(name_case)+1);
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

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, int tour) {
	plateau_t p;
	char cases[7][4] = { {"1  "}, {"2  "}, {"3  "}, {"4  "}, {"5  "}, {"6  "}, {"X  "} };
	for (int i = 0; i < LEN_BOARD; i++) {
		p.board[i] = init_chevaux(VIDE, -1, "#  ");
	}
	p.board[LEN_BOARD-1] = init_chevaux(BOARD_END, -1, "");
	//p.board[1] = init_chevaux(ROUGE, -1, "#  ");
	//p.board[15] = init_chevaux(JAUNE, -1, "#  ");
	//p.board[29] = init_chevaux(VERT, -1, "#  ");
	//p.board[43] = init_chevaux(BLEU, -1, "#  ");
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		
		p.rouge_f[i] = init_chevaux(ROUGE, -1, cases[i]);
	}
	//p.rouge_f[LEN_BOARD_FINAL-1] = init_chevaux(BOARD_END, -1, "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		
		p.vert_f[i] = init_chevaux(VERT, -1, cases[i]);
	}
	//p.bleu_f[LEN_BOARD_FINAL-1] = init_chevaux(BOARD_END, -1, "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		
		p.jaune_f[i] = init_chevaux(JAUNE, -1, cases[i]);
	}
	//p.jaune_f[LEN_BOARD_FINAL - 1] = init_chevaux(BOARD_END, -1, "");

	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		
		p.bleu_f[i] = init_chevaux(BLEU, -1, cases[i]);
	}
	//p.vert_f[LEN_BOARD_FINAL - 1] = init_chevaux(BOARD_END, -1, "");

	p.nb_joueurs = nb_joueurs;
	p.tour = tour;
	return p;
}

void tour_suivant(plateau_t p) {
	p.tour += 1 % p.nb_joueurs;
}

void modif_case(plateau_t p, joueur_t* j, int num_cheval) {
	p.board[j->chevaux[num_cheval].position + j->jet_des] = j->chevaux[num_cheval];
}

int est_mangeable(plateau_t p, joueur_t* j, int num_cheval, int pos_to_go) {
	if (j->couleur != p.board[pos_to_go].couleur) {
		return 1;
	}
	return 0;
}

void manger_cheval(plateau_t p, joueur_t* j, joueur_t* j_manger, int num_cheval) {
	int pos_to_go = j->jet_des + j->chevaux[num_cheval].position;
	if (est_mangeable(p, j, num_cheval, pos_to_go)) {
		j_manger->ecurie += 1;
		p.board[pos_to_go] = j->chevaux[num_cheval];
	}
	else {
		printf("Il y a deja un de vos chevaux a cette position relancez les des");
	}
}

int check_couleur_sortie(int couleur) {
	switch (couleur)
	{
	case ROUGE:
		return R_EC_SORTIE;
	case VERT:
		return G_EC_SORTIE;
	case JAUNE:
		return Y_EC_SORTIE;
	case BLEU:
		return B_EC_SORTIE;
	default:
		break;
	}
	return 0;
}

int is_win(plateau_t p) {
	if (p.bleu_f[LEN_BOARD_FINAL - 1].numero) {
		return BLEU;
	} 
	else if (p.rouge_f[LEN_BOARD_FINAL - 1].numero) {
		return ROUGE;
	}
	else if (p.vert_f[LEN_BOARD_FINAL - 1].numero) {
		return VERT;
	}
	else if (p.jaune_f[LEN_BOARD_FINAL - 1].numero) {
		return JAUNE;
	}
	return 0;
}

void sortie_ecurie(plateau_t p, joueur_t* j) {
	if (j->ecurie) {
		modif_case(p, j, check_couleur_sortie(j->couleur));
		j->ecurie -= 1;

	}
	else {
		printf("Impossible de sortir un cheval car %s n'a plus de chevaux dans son ecurie", j->nom);
	}
}

void print_elems(int n, ...) {
	va_list ap;
	chevaux_t i;

	va_start(ap, n);
	while (n--) {
		i = va_arg(ap, chevaux_t);
		if (i.couleur == ROUGE) {
			printf(KRED "%s" KNRM, i.name_case);
		}
		else if (i.couleur == VERT) {
			printf(KGRN "%s" KNRM, i.name_case);
		}
		else if (i.couleur == BLEU) {
			printf(KBLU "%s" KNRM, i.name_case);
		}
		else if (i.couleur == JAUNE) {
			printf(KYEL "%s" KNRM, i.name_case);
		}
		else {
			printf(KNRM "%s", i.name_case);
		}	
	}
	va_end(ap);
}

void desalloc_ptrs(void* arg, ...) {
	va_list args;
	void* element;
	free(arg);
	va_start(args, arg);
	while ((element = va_arg(args, void*)) != NULL) {
		free(element);
	}
	va_end(args);
}

/* affiche le plateau de jeu */
void affiche_plateau(plateau_t p) {
	chevaux_t l_idx;
	chevaux_t s_idx;
	int tmp;
	short is_colored = 0;
	int show_couleur = 0;
	int start_idx = 0;
	int i = 0;
	int last_idx = LEN_BOARD-2;
	for (; i < ROWS; i++) {
		//ligne 0 (premiere)
		if (i == 0) {
			printf("                  ");
			print_elems(3, p.board[last_idx], p.board[start_idx], p.board[start_idx + 1]);
			start_idx++;
		}
		//ligne 6 
		else if (i < 6) {
			printf("                  ");
			print_elems(3, p.board[last_idx], p.rouge_f[show_couleur], p.board[start_idx]);
			show_couleur++;
		}
		else if (i == 6) {

			last_idx -= 6;
			tmp = last_idx;
			for (int j = 0; j < 15; j++) {
				if (j == 0) {
					print_elems(1, p.board[last_idx]);
					last_idx++;
					continue;
				}
				else if (j < 7) {
					print_elems(1, p.board[last_idx]);
					last_idx++;
				}
				else if (j == 7) {
					print_elems(1, p.rouge_f[show_couleur]);
				}
				else {
					print_elems(1, p.board[start_idx]);
					start_idx++;
				}
			}
			last_idx = tmp - 1;
			show_couleur = 0;
			printf("\n");
			continue;
		}
		// ligne 7
		else if (i == 7) {
			
			for (int j = 0; j < 15; j++) {
				if (j == 0) {
					print_elems(1, p.board[last_idx]);
					last_idx--;	
				}
				else if (j == 14) {
					print_elems(1, p.board[start_idx]);
					start_idx++;
				}
				else if (j < 7) {
					print_elems(1, p.bleu_f[show_couleur]);
					show_couleur++;
				}
				else if (j == 7) {
					printf("X  ");
					show_couleur = 5;
				}
				else {
					print_elems(1, p.jaune_f[show_couleur]);
					show_couleur--;
				}
				
			}
			show_couleur = 0;
			printf("\n");
			continue;
		}
		//ligne 8
		else if (i == 8) {
			start_idx += 6;
			tmp = start_idx;
			show_couleur = 5;
			for (int j = 0; j < 15; j++) {
				if (j < 7) {
					print_elems(1, p.board[last_idx]);
					last_idx--;
				}
				else if (j == 7) {
					print_elems(1, p.vert_f[show_couleur]);
					show_couleur--;
				}
				else if (j == 14) {
					print_elems(1, p.board[start_idx]);
					start_idx--;
				}
				else {
					print_elems(1, p.board[start_idx]);
					start_idx--;
				} 
			}
			start_idx = tmp + 1;
			show_couleur = 4;
			printf("\n");
			continue;
		}
		//ligne 14 (derniere)
		else if (i == 14) {
			printf("                  ");
			print_elems(3, p.board[last_idx], p.board[start_idx + 1], p.board[start_idx]);
		}
		else if (i > 8 && i < 14) {
			printf("                  ");
			print_elems(3, p.board[last_idx], p.vert_f[show_couleur], p.board[start_idx]);
			show_couleur--;
		}
		start_idx++;
		last_idx--;
		printf("\n");
	}
}

void save(plateau_t board, char* path) {}

plateau_t load(char* path) {}
