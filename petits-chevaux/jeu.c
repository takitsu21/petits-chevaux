#include "jeu.h"
/* jet de des de 1 a 6 */
int jet_des() {
	srand(time(NULL));
	return rand() % 6 + 1;
}
/* nettoie le terminal*/
void cls() {
	system("cls");
}
/*recupere les input */
char* get_input() {
	int c;
	char* input = (char*)malloc(sizeof(char) * MAX_NAME);
	while (scanf(" %[^\n]", input) != 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Erreur, reessayer : ");
	}
	return input;
}
/* obtient le nombre de joueurs pour la partie */
int get_nb_joueurs() {
	int n;
	printf("Combien y a t-il de joueurs ? ");
	while (scanf(" %d", &n) != 1 || !(n >= 2 && n <= 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Reessayer, 2 a 4 joueurs max : ");
	}
	return n;
}
/* choix du tout debut de la partie */
int start_choice() {
	int n;
	printf("Bienvenue dans le jeu des petits chevaux\nChoississez parmis les 3 propositions suivantes :\n"\
		"\t[1] Nouvelle partie\n"\
		"\t[2] Quitter\n");
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || !(n >= 1 && n <= 2) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Nouvelle partie\n"\
			"\t[2] Quitter\n");
		printf("Choix :");
	}
	return n;
}
/* choix quand le joueur doit rejouer */
int choice_replay() {
	int n;
	printf("Encore a vous ! Vous avez fait 6\n");
	printf("Faites un choix :\n"\
		"\t[1] Sortie cheval de l'ecurie\n"\
		"\t[2] Avancer de 6 un de vos chevaux\n"\
		"\t[3] Sauvegarder la partie\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Sortie cheval de l'ecurie\n"\
			"\t[2] Avancer de 6 un de vos chevaux\n"\
			"\t[3] Sauvegarder la partie\nChoix : ");
	}
	return n;
}
/* affiche petit chevaux en ascii art */
void start_ascii() {
	printf("______    _   _ _          _                                \n");
	printf("| ___ \\  | | (_| |        | |                               \n");
	printf("| |_/ ___| |_ _| |_    ___| |__   _____   ____ _ _   ___  __\n");
	printf("|  __/ _ | __| | __|  / __| '_ \\ / _ \\ \\ / / _` | | | \\ \\/ /\n");
	printf("| | |  __| |_| | |_  | (__| | | |  __/\\ V | (_| | |_| |>  < \n");
	printf("\\_|  \\___|\\__|_|\\__|  \\___|_| |_|\\___| \\_/ \\__,_|\\__,_/_/\\_\\\n\n");
}
/* tout les chevaux du joueur qui sont sur le plateau */
chevaux_t* horses_on_board(joueur_t* j) {
	chevaux_t* horses_outside = NULL;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (j->chevaux[i].position != -1) {
			horses_outside = (chevaux_t*)realloc(horses_outside, (count + 1) * sizeof(chevaux_t));
			horses_outside[count] = j->chevaux[i];
			count++;
		}
	}
	if (horses_outside != NULL) {
		return horses_outside;
	}
	return NULL;
}
/* choisie un cheval disponible sur le plateau */
int choose_cheval(joueur_t* j) {
	int n;
	chevaux_t* horses_available = horses_on_board(j);
	printf("Choississez votre cheval a utiliser :\n");
	for (int i = 0; i < j->on_board; i++) {
		printf("\t[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
	}
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || is_valid_input(horses_available, n, 4) != 1) {
		while (getchar() != '\n');
		printf("Choississez votre cheval a utiliser :\n");
		for (int i = 0; i < j->on_board; i++) {
			printf("\t[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
		}
		printf("Choix : ");
	}
	return n - 1;
}
chevaux_t* horses_in_ecurie(joueur_t* j) {
	chevaux_t* horses_inside = NULL;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (j->chevaux[i].position == -1) {
			horses_inside = realloc(horses_inside, (count + 1) * sizeof(chevaux_t));
			horses_inside[count] = j->chevaux[i];
			count++;
		}
	}
	if (horses_inside != NULL) {
		return horses_inside;
	}
	return NULL;
}
int is_valid_input(chevaux_t* horses_available, int n, int ecurie) {
	if (horses_available == NULL) {
		return 0;
	}
	for (int i = 0; i < ecurie; i++) {
		if (horses_available[i].numero == n) {
			printf("%d %d\n", horses_available[i].numero, n);
			//system("pause");
			return 1;
		}
	}
	return 0;
}
int choose_cheval_ecurie(joueur_t* j) {
	int n;
	chevaux_t* horses_available = horses_in_ecurie(j);
	printf("Choississez votre cheval a utiliser :\n");
	for (int i = 0; i < j->ecurie; i++) {
		printf("		[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
	}
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || is_valid_input(horses_available, n, j->ecurie) != 1) {
		while (getchar() != '\n');
		printf("Choississez votre cheval a utiliser :\n");
		for (int i = 0; i < j->ecurie; i++) {
			if (horses_available[i].position == -1) {
				printf("		[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
			}
		}
		printf("Choix : ");
	}
	return n - 1;
}
int if_6() {
	int n;
	printf("Faites un choix :\n"\
		"          [1] Sortie cheval de l'ecurie\n"\
		"          [2] Jouer un cheval sur le terrain\n"\
		"          [3] Sauvegarder la partie\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"          [1] Jeter les des\n"\
			"          [2] Sortie cheval de l'ecurie\n"\
			"          [3] Sauvegarder la partie\nChoix : ");
	}
	return n;
}
int random_choice_pnj(joueur_t* j, chevaux_t* horses, int max) {
	int r_choice;
	srand(time(NULL));
	while (1) {
		r_choice = rand() % 4 + 1;
		Sleep(10);
		if (is_valid_input(horses, r_choice, 4)) {
			return r_choice;
		}
	}
	Sleep(200);
}
void sortie_ecurie(plateau_t* p, joueur_t* j, joueur_t* j_eat) {
	chevaux_t* horse;
	int idx_horse;
	int pos = j->sortie_pos;
	int _is_collide;
	if (j->is_pnj == 1) {
		horse = &j->chevaux[random_choice_pnj(j, horses_in_ecurie(j), j->ecurie) - 1];
	}
	else {
		horse = &j->chevaux[choose_cheval_ecurie(j)];
	}
	idx_horse = horse->numero - 1;
	_is_collide = is_collide(*p, *horse, pos);
	if (j_eat != NULL) {
		printf("%d %s %d\n", j_eat->couleur, j_eat->nom, j_eat->num_j);
		system("pause");
		j->tmp_case[idx_horse] = j_eat->tmp_case[j_eat->chevaux[p->board[pos].numero - 1].numero - 1];
		p->board[pos] = *horse;
		horse->position = j->sortie_pos;
		j->on_board += 1;
		j_eat->chevaux[p->board[pos].numero - 1].position = -1;
		j_eat->ecurie += 1;
		j_eat->on_board += 1;
		printf("Vous avez manger le cheval de %s\n", j_eat->nom);
	}
	else if (_is_collide == 0) {
		j->tmp_case[horse->numero - 1] = p->board[pos];
		horse->position = pos;
		p->board[pos] = *horse;
		j->ecurie -= 1;
		j->on_board += 1;
	}
	else {
		printf("Vous avez deja un cheval a cette position\n");
	}
}
/* mange un cheval ennemie */
void eat_horse(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos) {
	chevaux_t old_case = current_joueur->tmp_case[horse.numero - 1];
	int old_pos = horse.position;
	j_eat->chevaux[p->board[pos].numero - 1].position = -1;
	j_eat->on_board -= 1;
	j_eat->ecurie += 1;
	current_joueur->tmp_case[horse.numero - 1] = j_eat->tmp_case[p->board[pos].numero - 1];
	current_joueur->chevaux[horse.numero - 1].position = pos;
	p->board[pos] = current_joueur->chevaux[horse.numero - 1];
	p->board[old_pos] = old_case;
}
/* 1 si cheval ennemie, -1 si allie, 0 si case vide */
int is_collide(plateau_t p, chevaux_t horse, int pos) {
	chevaux_t horse_collide_check = p.board[pos];
	//system("pause");
	if (horse_collide_check.position >= 0 && horse_collide_check.position < 57) {
		if (horse_collide_check.couleur != horse.couleur) {
			return 1;
		}
		else {
			return -1;
		}
	}
	return 0;
}
/*nouvelle position si la marche d'escalier n'a pas ete atteinte*/
int new_pos_backward(joueur_t* j, int pos) {
	int first_stair = j->sortie_pos - 1;
	int new_pos;
	if (first_stair == 0) {
		first_stair += 56;
		pos += 56;
	}
	new_pos = first_stair - (pos - first_stair);
	return new_pos;
}
/*0 si elligible a monter, 1 si superieur au 1er escalier, -1 si inferieur*/
int is_elligible_prd(joueur_t* j, chevaux_t horse, int pos) {
	int first_stair = j->sortie_pos - 1;
	int tour_complet;
	if (horse.position == first_stair) {
		return 0;
	}
	if (first_stair == 0) {
		first_stair += 56;
		pos += 56;
	}
	tour_complet = first_stair - horse.position;
	if (tour_complet <= 6 && tour_complet >= 0) {
		if (horse.position == first_stair) {
			return 0; // elligible peut monter la pyramide
		}
		else if (horse.position + j->jet_des > first_stair) {
			return 1; // superieur, retourne en arriere
		}
	}
	return -1; // inferieur avance normalement
}
/* deplace un cheval */
void move_horse(plateau_t* p, chevaux_t* horse, joueur_t* current_joueur, int pos, chevaux_t tmp) {
	p->board[pos] = current_joueur->chevaux[horse->numero - 1];
	p->board[horse->position] = current_joueur->tmp_case[horse->numero - 1];
	current_joueur->tmp_case[horse->numero - 1] = tmp;
	current_joueur->chevaux[horse->numero - 1].position = pos;
}
/* si le cheval a fait un tour complet retourne en arriere du nombre de cases restant > au tour complet */
void go_back(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos) {
	chevaux_t tmp;
	if (horse.position == new_pos_backward(current_joueur, pos)) { //reste au meme endroit
		printf("reste au meme endroit\n");
		//system("pause");
	}
	else { // retourne en arriere
		if (pos != new_pos_backward(current_joueur, pos)) {
			pos = new_pos_backward(current_joueur, pos);
			if (j_eat == NULL) {
				tmp = p->board[pos];
				//move_horse(p, &horse, current_joueur, pos, tmp);
				p->board[pos] = current_joueur->chevaux[horse.numero - 1];
				p->board[horse.position] = current_joueur->tmp_case[horse.numero - 1];
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->chevaux[horse.numero - 1].position = pos;
			}
			else {
				eat_horse(p, current_joueur, horse, j_eat, pos);
			}
		}
	}
}
/* demande a l'utilisateur si un joueur est un pnj*/
int is_pnj() {
	int n;
	printf("Ce joueur sera-t-il un pnj ?\n"\
		"          [1] Oui\n"\
		"          [2] Non\n"\
		"Choix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nCe joueur sera-t-il un pnj ?\n"\
			"          [1] Oui\n"\
			"          [2] Non\n"\
			"Choix : ");
	}
	return n;
}
chevaux_t get_board_f_by_couleur(int couleur, plateau_t p) {
	switch (couleur)
	{
	case ROUGE:
		return *p.rouge_f;
	case BLEU:
		return *p.bleu_f;
	case VERT:
		return *p.vert_f;
	case JAUNE:
		return *p.jaune_f;
	default:
		break;
	}
}
/* deplace un cheval sur sa pyramide */
void move_prd(plateau_t* p, joueur_t* current_joueur, chevaux_t horse) {
	int old_pyrd;
	chevaux_t tmp;
	if (current_joueur->jet_des == horse.pos_pyrd || current_joueur->jet_des == horse.pos_pyrd - 1) {
		if (current_joueur->couleur == ROUGE) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->rouge_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					affiche_plateau(*p, current_joueur, horse);
					printf("Joueur gagnant %s couleur %d\n", current_joueur->nom, current_joueur->couleur);
					system("pause");
					exit(0);
				}
				tmp = p->rouge_f[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->sortie_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				p->rouge_f[horse.pos_pyrd - 1] = current_joueur->chevaux[horse.numero - 1];
				if (old_pyrd > 0) {
					p->rouge_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->chevaux[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
				system("pause");
			}
		}
		else if (current_joueur->couleur == BLEU) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->bleu_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					affiche_plateau(*p, current_joueur, horse);
					printf("Joueur gagnant %s couleur %d", current_joueur->nom, current_joueur->couleur);
					system("pause");
					exit(0);
				}
				tmp = p->bleu_f[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->sortie_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				p->bleu_f[horse.pos_pyrd - 1] = current_joueur->chevaux[horse.numero - 1];
				if (old_pyrd > 0) {
					p->bleu_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->chevaux[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
				system("pause");
			}
		}
		else if (current_joueur->couleur == JAUNE) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->jaune_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					affiche_plateau(*p, current_joueur, horse);
					printf("Joueur gagnant %s couleur %d", current_joueur->nom, current_joueur->couleur);
					system("pause");
					exit(0);
				}
				tmp = p->jaune_f[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->sortie_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				p->jaune_f[horse.pos_pyrd - 1] = current_joueur->chevaux[horse.numero - 1];
				if (old_pyrd > 0) {
					p->jaune_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->chevaux[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
				system("pause");
			}
		}
		else if (current_joueur->couleur == VERT) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->vert_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					affiche_plateau(*p, current_joueur, horse);
					printf("Joueur gagnant %s couleur %d", current_joueur->nom, current_joueur->couleur);
					system("pause");
					exit(0);
				}
				tmp = p->vert_f[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->sortie_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				p->vert_f[horse.pos_pyrd - 1] = current_joueur->chevaux[horse.numero - 1];
				if (old_pyrd > 0) {
					p->vert_f[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->chevaux[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
				system("pause");
			}
		}
	}
}
/* regarde si un cheval se collisionne avec un autre cheval de son equipe */
int is_collide_prd(plateau_t p, chevaux_t horse) {
	switch (horse.couleur) {
	case ROUGE:
		return p.rouge_f[horse.pos_pyrd].pos_pyrd != -1;
	case BLEU:
		return p.bleu_f[horse.pos_pyrd].pos_pyrd != -1;
	case JAUNE:
		return p.jaune_f[horse.pos_pyrd].pos_pyrd != -1;
	case VERT:
		return p.vert_f[horse.pos_pyrd].pos_pyrd != -1;
	default:
		break;
	}
}
/* gere les IAs du jeu */
void ia(plateau_t* p, joueur_t* current_joueur, joueur_t* joueurs) {
	joueur_t* j_manger;
	chevaux_t tmp;
	chevaux_t horse;
	int actual_pos;
	int out_or_play;
	current_joueur->jet_des = jet_des();
	if (current_joueur->on_board > 0) {
		if (is_6(current_joueur) && p->board[current_joueur->sortie_pos].position == -1) {
			srand(time(NULL));
			out_or_play = rand() % 2 + 1;
			if (out_or_play == 1 && p->board[current_joueur->sortie_pos].position == -1) { // sort un cheval puis rejoue
				sortie_ecurie(&p, current_joueur, NULL);
				horse = current_joueur->chevaux[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->jet_des) % 56;
				if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
							move_horse(&p, &horse, current_joueur, actual_pos, p->board[actual_pos]);
						}
						else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
							move_prd(&p, current_joueur, horse);
						}
						else {
							if (is_collide(*p, horse, actual_pos) == 1) {
								go_back(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(*p, horse, actual_pos) == 0) {
								go_back(&p, current_joueur, horse, NULL, actual_pos);
							}
						}
					}
					else if (is_collide(*p, horse, actual_pos) == -1) {
						while (is_collide(*p, horse, actual_pos) == -1) {
							current_joueur->jet_des = jet_des();
							actual_pos = (horse.position + current_joueur->jet_des) % 56;
						}
						if (is_collide(*p, horse, actual_pos) == 1) {
							eat_horse(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
						}
						else {
							if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								move_horse(&p, &horse, current_joueur, actual_pos, p->board[actual_pos]);
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse);
							}
							else {
								if (is_collide(*p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(*p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
						}
					}
					else {
						eat_horse(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(p, current_joueur, horse);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						printf("actual pos = %d", actual_pos);
						system("pause");
						go_back(p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(p, current_joueur, horse, NULL, actual_pos);
					}
				}
			}
			else {
				horse = current_joueur->chevaux[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->jet_des) % 56;
				if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						move_horse(&p, &horse, current_joueur, actual_pos, p->board[actual_pos]);
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(&p, current_joueur, horse);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						printf("actual pos = %d", actual_pos);
						system("pause");
						go_back(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(&p, current_joueur, horse, NULL, actual_pos);
					}
				}
				current_joueur->jet_des = jet_des();
				horse = current_joueur->chevaux[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->jet_des) % 56;
				if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						move_horse(&p, &horse, current_joueur, actual_pos, p->board[actual_pos]);
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(&p, current_joueur, horse);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						printf("actual pos = %d", actual_pos);
						system("pause");
						go_back(&p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(&p, current_joueur, horse, NULL, actual_pos);
					}
				}
			}
		}
		else {
			horse = current_joueur->chevaux[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
			actual_pos = (horse.position + current_joueur->jet_des) % 56;
			if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
				if (is_collide(*p, horse, actual_pos) == 1) {
					eat_horse(p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
				}
				else if (is_collide(*p, horse, actual_pos) == 0) {
					move_horse(p, &horse, current_joueur, actual_pos, p->board[actual_pos]);
				}
			}
			else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
				move_prd(p, current_joueur, horse);
			}
			else {
				if (is_collide(*p, horse, actual_pos) == 1) {
					go_back(p, current_joueur, horse, &joueurs[p->board[actual_pos].num_j - 1], actual_pos);
				}
				else if (is_collide(*p, horse, actual_pos) == 0) {
					go_back(p, current_joueur, horse, NULL, actual_pos);
				}
			}
		}
	}
	else {// si le joueur n'a toujours pas de chevaux sur le terrain
		if (is_6(current_joueur)) {
			if (p->board[current_joueur->sortie_pos].position == -1) {
				sortie_ecurie(p, current_joueur, NULL);
			}
		}
	}
	Sleep(400);
}
/* determine le tour actuel */
joueur_t* current_turn(plateau_t p, joueur_t* joueurs) {
	for (int i = 0; i < p.nb_joueurs; i++) {
		if (joueurs[i].is_playing) {
			return &joueurs[i];
		}
	}
}
/* fonction qui fait fonctionner tout le jeu */
void Game() {
	start_ascii();
	plateau_t p;
	joueur_t* current_joueur;
	joueur_t* j_manger;
	chevaux_t tmp;
	chevaux_t horse;
	joueur_t* joueurs = NULL;
	joueur_t* tour = NULL;
	char bots_name[4][10] = { {"HAL-9000"}, {"T-1000"}, {"R2D2"}, {"T-800"} };
	int sortie_posis[4] = { R_EC_SORTIE, B_EC_SORTIE, G_EC_SORTIE, Y_EC_SORTIE };
	int couleurs[4] = { ROUGE, BLEU, VERT, JAUNE };
	int actual_pos;
	int out_or_play;
	int nb_joueurs;
	int choose_idx;
	int old_pyrd;
	int if_6_res;
	int i;
	if (fsave_exists(SAVE_FILENAME)) { // verifie si une sauvegarde existe
		if (choice_load() == 1) {
			Game_t game = load_game();
			printf("Chargement...\n");
			p = game.p;
			joueurs = (joueur_t*)calloc(p.nb_joueurs, sizeof(joueur_t));
			for (int i = 0; i < p.nb_joueurs; i++) { // charge les joueurs
				joueurs[i] = game.joueurs[i];
			}
			printf("Le jeu a bien ete charger !\n");
			system("pause");
			tour = current_turn(p, joueurs);
			//tour = check_who_start(joueurs, p.nb_joueurs);
			i = tour->num_j - 1;
			goto start; // rentre dans la boucle while une fois toute les variables charger
		}
	}
	switch (start_choice()) // Choix du début
	{
	case NEW_GAME: // Nouvelle partie
		nb_joueurs = get_nb_joueurs();
		joueurs = (joueur_t*)calloc(nb_joueurs, sizeof(joueur_t));
		for (int i = 0; i < nb_joueurs; i++) { // initialise tout les joueurs
			if (is_pnj() == 1) {
				joueurs[i] = init_joueur(couleurs[i], i + 1, sortie_posis[i], 1, bots_name[i]);
			}
			else {
				printf("Nom du joueur %d : ", i + 1);
				joueurs[i] = init_joueur(couleurs[i], i + 1, sortie_posis[i], 0, get_input());
			}
		}		
		tour = check_who_start(joueurs, nb_joueurs);
		p = init_plateau(nb_joueurs, tour);
		i = tour->num_j - 1;
		cls();
		while (1) {
			start: // start si le fichier de sauvegarde est charger
			current_joueur = tour;
			current_joueur->is_playing = 1;
			//p.tour = *current_joueur;
			affiche_plateau(p, current_joueur, current_joueur->chevaux[0]);
			if (current_joueur->is_pnj == 1) {
				ia(&p, current_joueur, joueurs);
				tour = &joueurs[i];
				i = (i + 1) % p.nb_joueurs;
				continue;
			}
			switch (ingame_choice())
			{
			case JET_DES:
				if (current_joueur->on_board > 0) {
					current_joueur->jet_des = jet_des();
					printf("Vous avez obtenu %d au jet de des\n", current_joueur->jet_des);
					if (is_6(current_joueur)) {
						out_or_play = choice_replay();
						if (out_or_play == 1 && p.board[current_joueur->sortie_pos].position == -1) { // sort un cheval puis rejoue
							sortie_ecurie(&p, current_joueur, NULL);
							horse = current_joueur->chevaux[choose_cheval(current_joueur)];
							actual_pos = (horse.position + current_joueur->jet_des) % 56;
							if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
										move_horse(&p, &horse, current_joueur, actual_pos, p.board[actual_pos]);
									}
									else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
										move_prd(&p, current_joueur, horse);
									}
									else {
										if (is_collide(p, horse, actual_pos) == 1) {
											go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
										}
										else if (is_collide(p, horse, actual_pos) == 0) {
											go_back(&p, current_joueur, horse, NULL, actual_pos);
										}
									}
								}
								else if (is_collide(p, horse, actual_pos) == -1) {
									while (is_collide(p, horse, actual_pos) == -1) {
										current_joueur->jet_des = jet_des();
										actual_pos = (horse.position + current_joueur->jet_des) % 56;
									}
									if (is_collide(p, horse, actual_pos) == 1) {
										eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
									}
									else {
										if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
											move_horse(&p, &horse, current_joueur, actual_pos, p.board[actual_pos]);
										}
										else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
											move_prd(&p, current_joueur, horse);
										}
										else {
											if (is_collide(p, horse, actual_pos) == 1) {
												go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
											}
											else if (is_collide(p, horse, actual_pos) == 0) {
												go_back(&p, current_joueur, horse, NULL, actual_pos);
											}
										}
									}
								}
								else {
									eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
						}
						else {
							horse = current_joueur->chevaux[choose_cheval(current_joueur)];
							actual_pos = (horse.position + current_joueur->jet_des) % 56;
							if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									move_horse(&p, &horse, current_joueur, actual_pos, p.board[actual_pos]);
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
							current_joueur->jet_des = jet_des();
							printf("Vous rejouez automatiquement vous avez obtenu %d en lançant les des", current_joueur->jet_des);
							horse = current_joueur->chevaux[choose_cheval(current_joueur)];
							actual_pos = (horse.position + current_joueur->jet_des) % 56;
							if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									move_horse(&p, &horse, current_joueur, actual_pos, p.board[actual_pos]);
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
						}
					}
					else {
						horse = current_joueur->chevaux[choose_cheval(current_joueur)];
						actual_pos = (horse.position + current_joueur->jet_des) % 56;
						if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
							if (is_collide(p, horse, actual_pos) == 1) {
								eat_horse(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(p, horse, actual_pos) == 0) {
								printf("Vous avez obtenu %d au lancer de des\n", current_joueur->jet_des);
								move_horse(&p, &horse, current_joueur, actual_pos, p.board[actual_pos]);
							}
						}
						else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
							move_prd(&p, current_joueur, horse);
						}
						else {
							if (is_collide(p, horse, actual_pos) == 1) {
								go_back(&p, current_joueur, horse, &joueurs[p.board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(p, horse, actual_pos) == 0) {
								go_back(&p, current_joueur, horse, NULL, actual_pos);
							}
						}
					}
				}
				else {
					current_joueur->jet_des = jet_des();
					if (is_6(current_joueur)) {
						if (p.board[current_joueur->sortie_pos].position == -1) {
							sortie_ecurie(&p, current_joueur, NULL);
							printf("Vous avez sorti le cheval %s de votre ecurie\n", p.board[current_joueur->sortie_pos].name_case);
							system("pause");
						}
						else {
							printf("Case deja occupe reessayer\n");
							continue;
						}
					}
				}
				//Changement de joueur
				current_joueur->is_playing = 0;
				tour = &joueurs[i];
				i = (i + 1) % p.nb_joueurs; // change de tour
				break;
			case SAVE:
				save(p, joueurs); // sauvegarde la partie
				break;
			default:
				/*for (int i = 0; i < p.nb_joueurs; i++) {
					free(joueurs[i].nom);
				}
				//free(joueurs);
				printf("La memoire a bien ete desalloue !");*/
				exit(0);
				break;
			}
		}
	case QUIT:
		exit(0);
	default:
		break;
	}
}
/* determine le joueur qui commence */
joueur_t* check_who_start(joueur_t* joueurs, int nb_joueurs) {
	int max = 0;
	joueur_t* res = (joueur_t*)malloc(sizeof(joueur_t));
	for (int i = 0; i < nb_joueurs; i++) {
		if (joueurs[i].jet_des > max) {
			max = joueurs[i].jet_des;
			res = &joueurs[i];
		}
	}
	return res;
}
/* affiche les ecuries */
void print_ecuries(joueur_t* j) {
	int i = 0;
	while (i < 4) {
		if (j->chevaux[i].position == -1) {
			printf("%s", j->chevaux[i].name_case);
		}
		i++;
	}
	printf("\n");
}
/* choisis de charger une partie ou non */
int choice_load() {
	int n;
	printf("Une sauvegarde existe souhaitez vous la charger ?\n" \
		   "\t[1] Oui\n\t[2] Non\n");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Reesayer, Une sauvegarde existe souhaitez vous la charger ?\n" \
			"\t[1] Oui\n\t[2] Non\n");
	}
	return n;
}
/* regarde si une partie deja sauvegarder existe */
int fsave_exists(const char* file_name) { // https://www.zentut.com/c-tutorial/c-file-exists/
	FILE* f;
	if (f = fopen(file_name, "rb")) {
		fclose(f);
		return 1;
	}
	return 0;
}
/* affiche la case du centre */
void print_last_case(int couleur, chevaux_t horse) {
	switch (couleur) {
	case ROUGE:
		printf(KRED);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case BLEU:
		printf(KBLU);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case VERT:
		printf(KGRN);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case JAUNE:
		printf(KYEL);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	default:
		break;
	}
}
/*affiche l'etat du joueur (nom, ecurie, couleur)*/
void affiche_etat_joueur(joueur_t* j) {
	if (j != NULL) {
		switch (j->couleur)
		{
		case ROUGE:
			printf("Joueur %sROUGE " KNRM, KRED);
			printf("%s\n", j->nom);
			printf("Ecurie : ");
			printf(KRED);
			print_ecuries(j);
			printf(KNRM);
			break;
		case BLEU:
			printf("Joueur %sBLEU " KNRM, KBLU);
			printf("%s\n", j->nom);
			printf("Ecurie : ");
			printf(KBLU);
			print_ecuries(j);
			printf(KNRM);
			break;
		case VERT:
			printf("Joueur %sVERT " KNRM, KGRN);
			printf("%s\n", j->nom);
			printf("Ecurie : ");
			printf(KGRN);
			print_ecuries(j);
			printf(KNRM);
			break;
		case JAUNE:
			printf("Joueur %sJAUNE " KNRM, KYEL);
			printf("%s\n", j->nom);
			printf("Ecurie : ");
			printf(KYEL);
			print_ecuries(j);
			printf(KNRM);
			break;
		default:
			break;
		}
	}
}
/* initialise un joueur */
joueur_t init_joueur(int couleur, int num_j, int sortie_pos, int is_pnj, char* name) {
	char num_chevaux[4][4] = { {"C1 "}, {"C2 "}, {"C3 "}, {"C4 "} };
	joueur_t j;
	j.num_j = num_j;
	j.nom = (char*)calloc(strlen(name), sizeof(char));
	strcpy(j.nom, name);
	j.ecurie = 4;
	j.on_board = 0;
	j.sortie_pos = sortie_pos;
	j.couleur = couleur;
	j.jet_des = jet_des();
	j.is_pnj = is_pnj;
	j.is_playing = 0;
	for (int i = 0; i < 4; i++) {
		j.chevaux[i] = init_chevaux(couleur, i + 1, num_chevaux[i], num_j);
	}
	return j;
}
/* initialise un cheval */
chevaux_t init_chevaux(int couleur, int numero, char* name_case, int num_j) {
	chevaux_t chevaux;
	size_t len_name_case = strlen(name_case);
	chevaux.couleur = couleur;
	chevaux.numero = numero;
	chevaux.position = -1;
	chevaux.num_j = num_j;
	chevaux.pos_pyrd = 1;
	strcpy(chevaux.name_case, name_case);
	return chevaux;
}
/* different choix dans la partie */
int ingame_choice() {
	int n;
	printf("Faites un choix :\n"\
		"\t[1] Jeter les des\n"\
		"\t[2] Sauvegarder la partie\n"\
		"\t[3] Quitter le jeu\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Jeter les des\n"\
			"\t[2] Sauvegarder la partie\n"\
			"\t[3] Quitter le jeu\nChoix : ");
	}
	return n;
}
/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs) {
	plateau_t p;
	char cases[7][4] = { {"1  "}, {"2  "}, {"3  "}, {"4  "}, {"5  "}, {"6  "}, {"X  "} };
	for (int i = 0; i < LEN_BOARD; i++) {
		p.board[i] = init_chevaux(VIDE, -1, "#  ", NULL);
	}
	p.board[R_EC_SORTIE] = init_chevaux(ROUGE, -1, "#  ", NULL);
	p.board[G_EC_SORTIE] = init_chevaux(VERT, -1, "#  ", NULL);
	p.board[Y_EC_SORTIE] = init_chevaux(JAUNE, -1, "#  ", NULL);
	p.board[B_EC_SORTIE] = init_chevaux(BLEU, -1, "#  ", NULL);
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.rouge_f[i] = init_chevaux(ROUGE, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.vert_f[i] = init_chevaux(VERT, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.jaune_f[i] = init_chevaux(JAUNE, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.bleu_f[i] = init_chevaux(BLEU, -1, cases[i], NULL);
	}
	p.nb_joueurs = nb_joueurs;
	return p;
}
/* verifie si le joueur a fait 6 */
int is_6(joueur_t* j) {
	return j->jet_des == 6;
}
/* affiche un nombre n de case du plateau pour simplifie l'affichage des couleurs */
void print_elems(int n, ...) {
	va_list ap;
	chevaux_t board_case;
	va_start(ap, n);
	while (n--) {
		board_case = va_arg(ap, chevaux_t);
		if (board_case.couleur == ROUGE) {
			printf(KRED "%s" KNRM, board_case.name_case);
		}
		else if (board_case.couleur == VERT) {
			printf(KGRN "%s" KNRM, board_case.name_case);
		}
		else if (board_case.couleur == BLEU) {
			printf(KBLU "%s" KNRM, board_case.name_case);
		}
		else if (board_case.couleur == JAUNE) {
			printf(KYEL "%s" KNRM, board_case.name_case);
		}
		else if (board_case.position == -2) {
			continue;
		}
		else {
			printf(KNRM "%s", board_case.name_case);
		}
	}
	va_end(ap);
}
/* desalloue plusieurs ptr */
void desalloc_ptrs(void* arg, ...) {
	va_list args;
	void* ptr;
	free(arg);
	va_start(args, arg);
	while ((ptr = va_arg(args, void*)) != NULL) {
		free(ptr);
	}
	va_end(args);
}
/* affiche le plateau de jeu */
void affiche_plateau(plateau_t p, joueur_t* joueur, chevaux_t horse) {
	int tmp; //utiliser pour les cases lateral
	int show_couleur = 0;
	int start_idx = 0;
	int i = 0;
	int last_idx = LEN_BOARD - 1;
	cls();
	start_ascii();
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
					if (horse.pos_pyrd == 7) {
						print_last_case(joueur->couleur, horse);
					}
					else {
						printf("X  ");
					}
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
	affiche_etat_joueur(joueur);
}
/* sauvegarde la partie */
void save(plateau_t p, joueur_t* joueurs) {
	FILE* f;
	size_t str_size;
	f = fopen(SAVE_FILENAME, "wb");
	if (f == NULL) {
		fprintf(stderr, "Impossible d'ecrire le fichier de sauvegarde...");
		exit(1);
	}
	fwrite(&p, sizeof(plateau_t), 1, f);
	for (int i = 0; i < p.nb_joueurs; i++) {
		fwrite(&joueurs[i], sizeof(joueur_t), 1, f);
		str_size = strlen(joueurs[i].nom);
		fwrite(&str_size, sizeof(size_t), 1, f);
		fwrite(joueurs[i].nom, sizeof(char), str_size, f);
	}
	system("pause");
	fclose(f);
}
/* charge une partie */
Game_t load_game() {
	FILE* f;
	Game_t game;
	plateau_t p;
	joueur_t* joueurs = NULL;
	size_t str_size;
	f = fopen(SAVE_FILENAME, "rb");
	if (f == NULL) {
		fprintf(stderr, "Fichier introuvable...");
		exit(1);
	}
	fread(&p, sizeof(plateau_t), 1, f);
	joueurs = (joueur_t*)calloc(p.nb_joueurs, sizeof(joueur_t));
	for (int i = 0; i < p.nb_joueurs; i++) {
		fread(&joueurs[i], sizeof(joueur_t), 1, f);
		fread(&str_size, sizeof(size_t), 1, f); // je lis la taille de la chaine de caracteres
		joueurs[i].nom = (char*)malloc(sizeof(char) * str_size);
		fread(joueurs[i].nom, sizeof(char), str_size, f);
		if (joueurs[i].nom) {
			joueurs[i].nom[str_size] = '\0'; // delimite par un \0 sinon depassement du tableau
		}
	}
	fclose(f);
	game.joueurs = joueurs;
	game.p = p;
	return game;
}
