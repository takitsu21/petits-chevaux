#include "jeu.h"
/* jet de des de 1 a 6 */
int roll_dice() {
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
	char* tmp = (char*)malloc(sizeof(char) * MAX_NAME);
	char* input = NULL;
	while (scanf(" %[^\n]", tmp) != 1) {
		while (getchar() != '\n'); // vide le buffer
		cls();
		start_ascii();
		printf("Erreur, reessayer : ");
	}
	tmp[strlen(tmp)] = '\0';
	if (tmp) {
		input = (char*)calloc(strlen(tmp) + 1, sizeof(char));
		strcpy(input, tmp);
	}
	free(tmp);
	return input;
}
/* obtient le nombre de joueurs pour la partie */
int get_nb_players() {
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
/* regles du jeu */
void rules() {
	printf("REGLES: \n\tDeux, trois ou quatre joueurs disposent de deux pions-chevaux, \n"\
		"(quelquefois trois, voire quatre).\nPour sortir de l'ecurie, il faut faire un 6 avec le de."\
		"Le parcours \nse fait d'abord sur la peripherie, celle-ci est commune a tous les joueurs.\n"\
		"Lorsqu'un cheval arrive sur une case \noccupee par un concurrent, il le renvoie dans son ecurie (le depart).\n"\
		"Le jeu se joue avec un seul de, les chevaux circulent dans le sens des aiguilles d'une montre. Un 6 permet de rejouer.\n"\
		"Après avoir fait un tour complet, le joueur doit faire le chiffre exact pour s'arreter devant son escalier.\n"\
		"Si le chiffre est trop grand, il avance jusqu'a la case puis \nrecule du nombre \nde cases correspondant a la difference entre le chiffre a faire et le chiffre fait.\n"\
		"Exemple : pour arriver en bas de l'escalier un joueur doit faire 3 or il fait 4, il doit donc avancer de 3 et recule de 1,\n"\
		"ce qui fait que la prochaine fois il devra faire 1."\
		"Une fois que le joueur se trouve dans la case situee juste devant l'escalier de sa couleur,\n"\
		" il doit remonter marche par marche jusqu'au centre du jeu pour rentrer a l'ecurie.\n"\
		"Pour cela, le joueur doit obtenir a chaque fois le chiffre exact inscrit dans la case,\n"\
		" et encore un 6 pour arriver a la coupe (il suffit qu'un seul cheval y arrive pour faire gagner le joueur).\n"\
		"Chacun est libre de faire sortir le nombre de chevaux qu'il desire mais il ne peut \njouer qu'un seul cheval par tour, d'ou la strategie du jeu.");
}
/* choix du tout debut de la partie */
int start_choice() {
	int n;
	printf("\nBienvenue dans le jeu des petits chevaux !\n\nChoississez parmis les 2 propositions suivantes :\n"\
		"\t[1] Nouvelle partie\n"\
		"\t[2] Regles du jeu\n"\
		"\t[3] Quitter\n");
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || !(n >= 1 && n <= 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Nouvelle partie\n"\
			"\t[2] Regles du jeu\n"\
			"\t[3] Quitter\n");
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
		"\t[2] Avancer de 6 un de vos chevaux\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 3) == 1) {
		while (getchar() != '\n');
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Sortie cheval de l'ecurie\n"\
			"\t[2] Avancer de 6 un de vos chevaux\nChoix : ");
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
horse_t* horses_on_board(player_t* j) {
	horse_t* horses_outside = NULL;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (j->horse[i].position != -1) {
			horses_outside = (horse_t*)realloc(horses_outside, (count + 1) * sizeof(horse_t));
			horses_outside[count] = j->horse[i];
			count++;
		}
	}
	if (horses_outside != NULL) {
		return horses_outside;
	}
	return NULL;
}
/* choisie un cheval disponible sur le plateau */
int choose_horse(player_t* j) {
	int n;
	horse_t* horses_available = horses_on_board(j);
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
	free(horses_available);
	return n - 1;
}
horse_t* horses_in_ecurie(player_t* j) {
	horse_t* horses_inside = NULL;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (j->horse[i].position == -1) {
			horses_inside = realloc(horses_inside, (count + 1) * sizeof(horse_t));
			horses_inside[count] = j->horse[i];
			count++;
		}
	}
	if (horses_inside != NULL) {
		return horses_inside;
	}
	return NULL;
}
int is_valid_input(horse_t* horses_available, int n, int ecurie) {
	if (horses_available == NULL) {
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		if (horses_available[i].numero == n) {
			return 1;
		}
	}
	return 0;
}
int choose_horse_ecurie(player_t* j) {
	int n;
	horse_t* horses_available = horses_in_ecurie(j);
	printf("Choississez votre cheval a utiliser :\n");
	for (int i = 0; i < j->ecurie; i++) {
		printf("\t[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
	}
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || is_valid_input(horses_available, n, j->ecurie) != 1) {
		while (getchar() != '\n');
		printf("Choississez votre cheval a utiliser :\n");
		for (int i = 0; i < j->ecurie; i++) {
			if (horses_available[i].position == -1) {
				printf("\t[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
			}
		}
		printf("Choix : ");
	}
	free(horses_available);
	return n - 1;
}
int if_6() {
	int n;
	printf("Faites un choix :\n"\
		"\t[1] Sortie cheval de l'ecurie\n"\
		"\t[2] Jouer un cheval sur le terrain\n"\
		"\t[3] Sauvegarder la partie\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"\t[1] Jeter les des\n"\
			"\t[2] Sortie cheval de l'ecurie\n"\
			"\t[3] Sauvegarder la partie\nChoix : ");
	}
	return n;
}
int random_choice_pnj(player_t* j, horse_t* horses, int max) {
	int r_choice;
	srand(time(NULL));
	while (1) {
		r_choice = rand() % 4 + 1;
		Sleep(10);
		if (is_valid_input(horses, r_choice, 4)) {
			return r_choice;
		}
	}
}
void sortie_ecurie(board_t* p, player_t* j, player_t* players) {
	horse_t* horse;
	int pos = j->out_pos;
	player_t* j_eat = NULL;
	if (p->board[pos].position != -1) {
		 j_eat = &players[p->board[pos].num_j - 1];
	}
	int idx_horse;
	if (j->is_pnj == 1) {
		horse = &j->horse[random_choice_pnj(j, horses_in_ecurie(j), j->ecurie) - 1];
	}
	else {
		horse = &j->horse[choose_horse_ecurie(j)];
	}
	idx_horse = horse->numero - 1;
	if (j_eat != NULL) {
		if (j_eat->color != j->color) {
			j->tmp_case[idx_horse] = j_eat->tmp_case[j_eat->horse[p->board[pos].numero - 1].numero - 1];
			horse->position = pos;
			p->board[pos] = *horse;
			j->ecurie -= 1;
			j->on_board += 1;
			j_eat->horse[p->board[pos].numero - 1].position = -1;
			j_eat->ecurie += 1;
			j_eat->on_board -= 1;
			printf("Vous avez manger le cheval de %s en sortant votre cheval %s\n", j_eat->name, horse->name_case);
		}
	}
	else if (is_collide(*p, *horse, pos) == 0) {
		j->tmp_case[horse->numero - 1] = p->board[pos];
		horse->position = pos;
		p->board[pos] = *horse;
		j->ecurie -= 1;
		j->on_board += 1;
		printf("Vous avez sorti le cheval %s de votre ecurie\n", horse->name_case);
	}
	else {
		printf("Vous avez deja un cheval a cette position\n");
	}
}
/* mange un cheval ennemie */
void eat_horse(board_t* p, player_t* current_joueur, horse_t horse, player_t* j_eat, int pos) {
	horse_t old_case = current_joueur->tmp_case[horse.numero - 1];
	int old_pos = horse.position;
	printf("Le cheval %s de %s a ete manger par %s\n", p->board[pos].name_case, j_eat->name, current_joueur->name);
	j_eat->horse[p->board[pos].numero - 1].position = -1;
	j_eat->on_board -= 1;
	j_eat->ecurie += 1;
	current_joueur->tmp_case[horse.numero - 1] = j_eat->tmp_case[p->board[pos].numero - 1];
	current_joueur->horse[horse.numero - 1].position = pos;
	p->board[pos] = current_joueur->horse[horse.numero - 1];
	p->board[old_pos] = old_case;
	p->board[old_pos].position = -1;
	Sleep(1000);
}
/* 1 si cheval ennemie, -1 si allie, 0 si case vide */
int is_collide(board_t p, horse_t horse, int pos) {
	horse_t horse_collide_check = p.board[pos];
	if (horse_collide_check.position >= 0 && horse_collide_check.position < 57) {
		if (horse_collide_check.color != horse.color) {
			return 1;
		}
		else {
			return -1;
		}
	}
	return 0;
}
/*nouvelle position si la marche d'escalier n'a pas ete atteinte*/
int new_pos_backward(player_t* j, int pos) {
	int first_stair = j->out_pos - 1;
	int new_pos;
	if (first_stair == 0) {
		first_stair += 56;
		pos += 56;
	}
	new_pos = first_stair - (pos - first_stair);
	return new_pos;
}
/*0 si elligible a monter, 1 si superieur au 1er escalier, -1 si inferieur*/
int is_elligible_prd(player_t* j, horse_t horse, int pos) {
	int first_stair = j->out_pos - 1;
	int full_turn;
	if (horse.position == first_stair) {
		return 0;
	}
	if (first_stair == 0) {
		first_stair += 56;
		pos += 56;
	}
	full_turn = first_stair - horse.position;
	if (full_turn <= 6 && full_turn >= 0) {
		if (horse.position == first_stair) {
			return 0; // elligible peut monter la pyramide
		}
		else if (horse.position + j->roll_dice > first_stair) {
			return 1; // superieur, retourne en arriere
		}
	}
	return -1; // inferieur avance normalement
}
/* deplace un cheval */
void move_horse(board_t* p, horse_t horse, player_t* current_joueur, int pos, horse_t tmp) {
	p->board[pos] = current_joueur->horse[horse.numero - 1];
	p->board[horse.position] = current_joueur->tmp_case[horse.numero - 1];
	current_joueur->tmp_case[horse.numero - 1] = tmp;
	current_joueur->horse[horse.numero - 1].position = pos;
}
/* si le cheval a fait un tour complet retourne en arriere du nombre de cases restant > au tour complet */
void go_back(board_t* p, player_t* current_joueur, horse_t horse, player_t* j_eat, int pos) {
	int new_pos_back = new_pos_backward(current_joueur, pos);
	if (horse.position == new_pos_back) { //reste au meme endroit
		printf("reste au meme endroit\n");
	}
	else { // retourne en arriere
		if (pos != new_pos_back) {
			pos = new_pos_backward(current_joueur, pos);
			if (j_eat == NULL) {
				move_horse(p, horse, current_joueur, pos, p->board[pos]);
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
		"\t[1] Oui\n"\
		"\t[2] Non\n"\
		"Choix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nCe joueur sera-t-il un pnj ?\n"\
			"\t[1] Oui\n"\
			"\t[2] Non\n"\
			"Choix : ");
	}
	return n;
}
/* deplace un cheval sur sa pyramide */
void move_prd(board_t* p, player_t* current_joueur, horse_t horse, player_t* players) {
	int old_pyrd; // valeur du cheval dans la pyramide - 1
	horse_t tmp;
	if (current_joueur->roll_dice == horse.pos_pyrd || current_joueur->roll_dice == horse.pos_pyrd - 1) {
		if (current_joueur->color == RED) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->red_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					show_board(*p, current_joueur, horse);
					printf("Joueur gagnant ");
					printf(KRED"%s\n"KNRM, current_joueur->name);
					desalloc_players(players, p->nb_players);
				}
				tmp = p->red_final[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->out_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				p->red_final[horse.pos_pyrd - 1] = current_joueur->horse[horse.numero - 1];
				if (old_pyrd > 0) {
					p->red_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->horse[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
			}
		}
		else if (current_joueur->color == BLUE) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->blue_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					show_board(*p, current_joueur, horse);
					printf("Joueur gagnant ");
					printf(KBLU"%s\n"KNRM, current_joueur->name);
					desalloc_players(players, p->nb_players);
				}
				tmp = p->blue_final[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->out_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				p->blue_final[horse.pos_pyrd - 1] = current_joueur->horse[horse.numero - 1];
				if (old_pyrd > 0) {
					p->blue_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->horse[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
			}
		}
		else if (current_joueur->color == YELLOW) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->yellow_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					show_board(*p, current_joueur, horse);
					printf("Joueur gagnant ");
					printf(KYEL"%s\n"KNRM, current_joueur->name);
					desalloc_players(players, p->nb_players);
				}
				tmp = p->yellow_final[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->out_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				p->yellow_final[horse.pos_pyrd - 1] = current_joueur->horse[horse.numero - 1];
				if (old_pyrd > 0) {
					p->yellow_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->horse[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
			}
		}
		else if (current_joueur->color == GREEN) {
			if (horse.pos_pyrd < 8) {
				old_pyrd = horse.pos_pyrd - 1;
				if (is_6(current_joueur) && horse.pos_pyrd == 7) {
					horse.pos_pyrd = 7;
					p->green_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					show_board(*p, current_joueur, horse);
					printf("Joueur gagnant ");
					printf(KGRN"%s\n"KNRM, current_joueur->name);
					desalloc_players(players, p->nb_players);
				}
				tmp = p->green_final[old_pyrd];
				if (horse.pos_pyrd == 1) {
					p->board[current_joueur->out_pos - 1] = current_joueur->tmp_case[horse.numero - 1];
				}
				p->green_final[horse.pos_pyrd - 1] = current_joueur->horse[horse.numero - 1];
				if (old_pyrd > 0) {
					p->green_final[old_pyrd - 1] = current_joueur->tmp_case[horse.numero - 1];
					horse.position = -2;
				}
				current_joueur->tmp_case[horse.numero - 1] = tmp;
				current_joueur->horse[horse.numero - 1].pos_pyrd += 1;
			}
			else {
				printf("Vous devez faire un 6 pour gagner");
			}
		}
	}
}
/* regarde si un cheval se collisionne avec un autre cheval de son equipe */
int is_collide_prd(board_t p, horse_t horse) {
	switch (horse.color) {
	case RED:
		return p.red_final[horse.pos_pyrd].pos_pyrd != -1;
	case BLUE:
		return p.blue_final[horse.pos_pyrd].pos_pyrd != -1;
	case YELLOW:
		return p.yellow_final[horse.pos_pyrd].pos_pyrd != -1;
	case GREEN:
		return p.green_final[horse.pos_pyrd].pos_pyrd != -1;
	default:
		break;
	}
}
/* gere les IAs du jeu */
void ia(board_t* p, player_t* current_joueur, player_t* players) {
	player_t* j_eat;
	horse_t tmp;
	horse_t horse;
	int actual_pos;
	int out_or_play;
	current_joueur->roll_dice = roll_dice();
	printf("Vous avez obtenu %d en jetant les des\n", current_joueur->roll_dice);
	Sleep(200);
	if (current_joueur->on_board > 0) {
		if (is_6(current_joueur) && p->board[current_joueur->out_pos].position == -1) {
			srand(time(NULL));
			out_or_play = 2;
			if (out_or_play == 1 && p->board[current_joueur->out_pos].position == -1) { // sort un cheval puis rejoue
				if (current_joueur->ecurie > 0) {
					sortie_ecurie(p, current_joueur, players);
				}
				horse = current_joueur->horse[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->roll_dice) % 56;
				if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
							move_horse(p, horse, current_joueur, actual_pos, p->board[actual_pos]);
						}
						else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
							move_prd(p, current_joueur, horse, players);
						}
						else {
							if (is_collide(*p, horse, actual_pos) == 1) {
								go_back(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(*p, horse, actual_pos) == 0) {
								go_back(p, current_joueur, horse, NULL, actual_pos);
							}
						}
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(p, current_joueur, horse, players);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						go_back(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(p, current_joueur, horse, NULL, actual_pos);
					}
				}
			}
			else {
				horse = current_joueur->horse[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->roll_dice) % 56;
				if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						move_horse(p, horse, current_joueur, actual_pos, p->board[actual_pos]);
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(p, current_joueur, horse, players);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						go_back(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(p, current_joueur, horse, NULL, actual_pos);
					}
				}
				Sleep(900);
				current_joueur->roll_dice = roll_dice();
				printf("Vous jouez une nouvelle fois, vous avez obtenu %d en jetant les des\n", current_joueur->roll_dice);
				horse = current_joueur->horse[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
				actual_pos = (horse.position + current_joueur->roll_dice) % 56;
				if (horse.pos_pyrd == 6 && current_joueur->roll_dice == 6) {
					move_prd(p, current_joueur, horse, players);
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
					if (is_collide(*p, horse, actual_pos) == 1) {
						eat_horse(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						move_horse(p, horse, current_joueur, actual_pos, p->board[actual_pos]);
					}
				}
				else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
					move_prd(p, current_joueur, horse, players);
				}
				else {
					if (is_collide(*p, horse, actual_pos) == 1) {
						go_back(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
					}
					else if (is_collide(*p, horse, actual_pos) == 0) {
						go_back(p, current_joueur, horse, NULL, actual_pos);
					}
				}
			}
		}
		else {
			horse = current_joueur->horse[random_choice_pnj(current_joueur, horses_on_board(current_joueur), 4) - 1];
			actual_pos = (horse.position + current_joueur->roll_dice) % 56;
			if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
				if (is_collide(*p, horse, actual_pos) == 1) {
					eat_horse(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
				}
				else if (is_collide(*p, horse, actual_pos) == 0) {
					move_horse(p, horse, current_joueur, actual_pos, p->board[actual_pos]);
				}
			}
			else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
				move_prd(p, current_joueur, horse, players);
			}
			else {
				if (is_collide(*p, horse, actual_pos) == 1) {
					go_back(p, current_joueur, horse, &players[p->board[actual_pos].num_j - 1], actual_pos);
				}
				else if (is_collide(*p, horse, actual_pos) == 0) {
					go_back(p, current_joueur, horse, NULL, actual_pos);
				}
			}
		}
	}
	else { // si le joueur n'a toujours pas de chevaux sur le terrain
		if (is_6(current_joueur)) {
			sortie_ecurie(p, current_joueur, players);
		}
	}
	Sleep(900);
}
/* determine le tour actuel */
player_t* current_turn(board_t p, player_t* players) {
	for (int i = 0; i < p.nb_players; i++) {
		if (players[i].is_playing) {
			return &players[i];
		}
	}
}
/* fonction qui fait fonctionner tout le jeu */
void Game() {
	start_ascii();
	board_t p;
	player_t* current_joueur;
	player_t* j_eat;
	horse_t tmp;
	horse_t horse;
	player_t* players = NULL;
	player_t* tour = NULL;
	char bots_name[4][10] = { {"HAL-9000"}, {"T-1000"}, {"R2D2"}, {"T-800"} };
	int out_posis[4] = { R_EC_OUT, B_EC_OUT, G_EC_OUT, Y_EC_OUT };
	int couleurs[4] = { RED, BLUE, GREEN, YELLOW };
	int actual_pos;
	int out_or_play;
	int nb_players;
	int choose_idx;
	int old_pyrd;
	int if_6_res;
	int i;
	if (fsave_exists(SAVE_FILENAME)) { // verifie si une sauvegarde existe
		if (choice_load() == 1) {
			Game_t game = load_game();
			printf("Chargement...\n");
			p = game.p;
			players = (player_t*)calloc(p.nb_players, sizeof(player_t));
			for (int i = 0; i < p.nb_players; i++) { // charge les players
				players[i] = game.players[i];
			}
			desalloc_players(game.players, p.nb_players);
			printf("Le jeu a bien ete charger !\n");
			tour = current_turn(p, players);
			//tour = check_who_start(players, p.nb_players);
			i = tour->num_j - 1;
			goto start; // rentre dans la boucle while une fois toutes les structures charger
		}
	}
	switch (start_choice()) // Choix du debut
	{
	case NEW_GAME: // Nouvelle partie
		nb_players = get_nb_players();
		players = (player_t*)calloc(nb_players, sizeof(player_t));
		for (int i = 0; i < nb_players; i++) { // initialise tout les players
			printf("Joueur %d : ", i + 1);
			if (is_pnj() == 1) {
				players[i] = init_joueur(couleurs[i], i + 1, out_posis[i], 1, bots_name[i]);
			}
			else {
				printf("Nom du joueur : ");
				players[i] = init_joueur(couleurs[i], i + 1, out_posis[i], 0, get_input());
			}
		}		
		tour = check_who_start(players, nb_players);
		printf("Joueur %s a eu le plus grand score au lancer de des, il commence\n", tour->name);
		p = init_board(nb_players, tour);
		i = tour->num_j - 1;
		system("pause");
		cls();
		while (1) {
			start: // start si le fichier de sauvegarde est charger
			current_joueur = tour;
			current_joueur->is_playing = 1;
			show_board(p, current_joueur, current_joueur->horse[0]);
			if (current_joueur->is_pnj == 1) {
				ia(&p, current_joueur, players);
				i = (i + 1) % p.nb_players;
				tour = &players[i];
				continue;
			}
			switch (ingame_choice())
			{
			case ROLL_DICE:
				if (current_joueur->on_board > 0) {
					current_joueur->roll_dice = roll_dice();
					printf("Vous avez obtenu %d au jet de des\n", current_joueur->roll_dice);
					if (is_6(current_joueur)) {
						out_or_play = choice_replay();
						if (out_or_play == 1 && p.board[current_joueur->out_pos].position == -1) { // sort un cheval puis rejoue
							if (current_joueur->ecurie > 0) {
								sortie_ecurie(&p, current_joueur, players);
							}
							horse = current_joueur->horse[choose_horse(current_joueur)];
							actual_pos = (horse.position + current_joueur->roll_dice) % 56;
							if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
										move_horse(&p, horse, current_joueur, actual_pos, p.board[actual_pos]);
									}
									else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
										move_prd(&p, current_joueur, horse, players);
									}
									else {
										if (is_collide(p, horse, actual_pos) == 1) {
											go_back(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
										}
										else if (is_collide(p, horse, actual_pos) == 0) {
											go_back(&p, current_joueur, horse, NULL, actual_pos);
										}
									}
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse, players);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
						}
						else {
							horse = current_joueur->horse[choose_horse(current_joueur)];
							actual_pos = (horse.position + current_joueur->roll_dice) % 56;
							if (horse.pos_pyrd == 6) {
								move_prd(&p, current_joueur, horse, players);
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									move_horse(&p, horse, current_joueur, actual_pos, p.board[actual_pos]);
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse, players);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
							Sleep(900);
							current_joueur->roll_dice = roll_dice();
							printf("Vous rejouez automatiquement vous avez obtenu %d en lancant les des", current_joueur->roll_dice);
							horse = current_joueur->horse[choose_horse(current_joueur)];
							actual_pos = (horse.position + current_joueur->roll_dice) % 56;
							if (horse.pos_pyrd == 6 && current_joueur->roll_dice == 6) {
								move_prd(&p, current_joueur, horse, players);
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
								if (is_collide(p, horse, actual_pos) == 1) {
									eat_horse(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									move_horse(&p, horse, current_joueur, actual_pos, p.board[actual_pos]);
								}
							}
							else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
								move_prd(&p, current_joueur, horse, players);
							}
							else {
								if (is_collide(p, horse, actual_pos) == 1) {
									go_back(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
								}
								else if (is_collide(p, horse, actual_pos) == 0) {
									go_back(&p, current_joueur, horse, NULL, actual_pos);
								}
							}
						}
					}
					else {
						horse = current_joueur->horse[choose_horse(current_joueur)];
						actual_pos = (horse.position + current_joueur->roll_dice) % 56;
						if (is_elligible_prd(current_joueur, horse, actual_pos) == -1) {
							if (is_collide(p, horse, actual_pos) == 1) {
								eat_horse(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(p, horse, actual_pos) == 0) {
								printf("Vous avez obtenu %d au lancer de des\n", current_joueur->roll_dice);
								move_horse(&p, horse, current_joueur, actual_pos, p.board[actual_pos]);
							}
						}
						else if (is_elligible_prd(current_joueur, horse, actual_pos) == 0) {
							move_prd(&p, current_joueur, horse, players);
						}
						else {
							if (is_collide(p, horse, actual_pos) == 1) {
								go_back(&p, current_joueur, horse, &players[p.board[actual_pos].num_j - 1], actual_pos);
							}
							else if (is_collide(p, horse, actual_pos) == 0) {
								go_back(&p, current_joueur, horse, NULL, actual_pos);
							}
						}
					}
				}
				else {
					current_joueur->roll_dice = roll_dice();
					printf("Vous avez obtenu %d au jet de des\n", current_joueur->roll_dice);
					if (is_6(current_joueur)) {
						sortie_ecurie(&p, current_joueur, players);
					}
					Sleep(500);
				}
				//Changement de joueur
				i = (i + 1) % p.nb_players;
				tour = &players[i];
				break;
			case SAVE:
				save(p, players); // sauvegarde la partie
				break;
			case QUIT:
				desalloc_players(players, p.nb_players); // desalloue les players et quitte le jeu
				free(tour);
				break;
			default:
				break;
			}
		}
	case QUIT:
		exit(0); // quitte le jeu
		break;
	case RULES:
		cls();
		start_ascii();
		rules();
		system("pause");
		cls();
		Game();
	default:
		break;
	}
}
/* desalloue proprement tout les players */
void desalloc_players(player_t* players, int nb_players) {
	for (int i = 0; i < nb_players; i++) {
		free(players[i].name);
	}
	free(players);
	printf("Memoire desalloue avec succes !\n");
	system("pause");
	exit(0);
}
/* determine le joueur qui commence */
player_t* check_who_start(player_t* players, int nb_players) {
	int max = 0;
	player_t* res = (player_t*)malloc(sizeof(player_t));
	for (int i = 0; i < nb_players; i++) {
		if (players[i].roll_dice > max) {
			max = players[i].roll_dice;
			res = &players[i];
		}
	}
	return res;
}
/* affiche les ecuries */
void print_ecuries(player_t* j) {
	int i = 0;
	while (i < 4) {
		if (j->horse[i].position == -1) {
			printf("%s", j->horse[i].name_case);
		}
		i++;
	}
	printf("\n");
}
/* choisis de charger une partie ou non */
int choice_load() {
	int n;
	printf("Une sauvegarde existe souhaitez vous la charger ?\n" \
		   "\t[1] Oui\n\t[2] Non\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Reesayer, Une sauvegarde existe souhaitez vous la charger ?\n" \
			"\t[1] Oui\n\t[2] Non\nChoix : ");
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
void print_last_case(int couleur, horse_t horse) {
	switch (couleur) {
	case RED:
		printf(KRED);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case BLUE:
		printf(KBLU);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case GREEN:
		printf(KGRN);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	case YELLOW:
		printf(KYEL);
		printf("%s", horse.name_case);
		printf(KNRM);
		break;
	default:
		break;
	}
}
/*affiche l'etat du joueur (nom, ecurie, couleur)*/
void affiche_etat_joueur(player_t* j) {
	if (j != NULL) {
		switch (j->color)
		{
		case RED:
			printf("Joueur %sROUGE " KNRM, KRED);
			printf("%s\n", j->name);
			printf("Ecurie : ");
			printf(KRED);
			print_ecuries(j);
			printf(KNRM);
			break;
		case BLUE:
			printf("Joueur %sBLEU " KNRM, KBLU);
			printf("%s\n", j->name);
			printf("Ecurie : ");
			printf(KBLU);
			print_ecuries(j);
			printf(KNRM);
			break;
		case GREEN:
			printf("Joueur %sVERT " KNRM, KGRN);
			printf("%s\n", j->name);
			printf("Ecurie : ");
			printf(KGRN);
			print_ecuries(j);
			printf(KNRM);
			break;
		case YELLOW:
			printf("Joueur %sJAUNE " KNRM, KYEL);
			printf("%s\n", j->name);
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
player_t init_joueur(int couleur, int num_j, int out_pos, int is_pnj, char* name) {
	char num_chevaux[4][4] = { {"C1 "}, {"C2 "}, {"C3 "}, {"C4 "} };
	player_t j;
	j.num_j = num_j;
	j.name = (char*)calloc(strlen(name) + 1, sizeof(char));
	//j.name = name;
	strcpy(j.name, name);
	if (is_pnj == 0) {
		free(name);
	}
	j.ecurie = 4;
	j.on_board = 0;
	j.out_pos = out_pos;
	j.color = couleur;
	j.roll_dice = roll_dice();
	j.is_pnj = is_pnj;
	j.is_playing = 0;
	for (int i = 0; i < 4; i++) {
		j.horse[i] = init_horses(couleur, i + 1, num_chevaux[i], num_j);
	}
	return j;
}
/* initialise un cheval */
horse_t init_horses(int couleur, int numero, char* name_case, int num_j) {
	horse_t chevaux;
	size_t len_name_case = strlen(name_case);
	chevaux.color = couleur;
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
board_t init_board(int nb_players) {
	board_t p;
	char cases[7][4] = { {"1  "}, {"2  "}, {"3  "}, {"4  "}, {"5  "}, {"6  "}, {"X  "} };
	for (int i = 0; i < LEN_BOARD; i++) {
		p.board[i] = init_horses(VIDE, -1, "#  ", NULL);
	}
	p.board[R_EC_OUT] = init_horses(RED, -1, "#  ", NULL);
	p.board[G_EC_OUT] = init_horses(GREEN, -1, "#  ", NULL);
	p.board[Y_EC_OUT] = init_horses(YELLOW, -1, "#  ", NULL);
	p.board[B_EC_OUT] = init_horses(BLUE, -1, "#  ", NULL);
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.red_final[i] = init_horses(RED, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.green_final[i] = init_horses(GREEN, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.yellow_final[i] = init_horses(YELLOW, -1, cases[i], NULL);
	}
	for (int i = 0; i < LEN_BOARD_FINAL; i++) {
		p.blue_final[i] = init_horses(BLUE, -1, cases[i], NULL);
	}
	p.nb_players = nb_players;
	return p;
}
/* verifie si le joueur a fait 6 */
int is_6(player_t* j) {
	return j->roll_dice == 6;
}
/* affiche un nombre n de case du plateau pour simplifie l'affichage des couleurs */
void print_elems(int n, ...) {
	va_list ap;
	horse_t board_case;
	va_start(ap, n);
	while (n--) {
		board_case = va_arg(ap, horse_t);
		if (board_case.color == RED) {
			printf(KRED "%s" KNRM, board_case.name_case);
		}
		else if (board_case.color == GREEN) {
			printf(KGRN "%s" KNRM, board_case.name_case);
		}
		else if (board_case.color == BLUE) {
			printf(KBLU "%s" KNRM, board_case.name_case);
		}
		else if (board_case.color == YELLOW) {
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
/* affiche le plateau de jeu */
void show_board(board_t p, player_t* joueur, horse_t horse) {
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
			print_elems(3, p.board[last_idx], p.red_final[show_couleur], p.board[start_idx]);
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
					print_elems(1, p.red_final[show_couleur]);
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
					print_elems(1, p.blue_final[show_couleur]);
					show_couleur++;
				}
				else if (j == 7) {
					if (horse.pos_pyrd == 7) {
						print_last_case(joueur->color, horse);
					}
					else {
						printf("X  ");
					}
					show_couleur = 5;
				}
				else {
					print_elems(1, p.yellow_final[show_couleur]);
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
					print_elems(1, p.green_final[show_couleur]);
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
			print_elems(3, p.board[last_idx], p.green_final[show_couleur], p.board[start_idx]);
			show_couleur--;
		}
		start_idx++;
		last_idx--;
		printf("\n");
	}
	printf("\n");
	affiche_etat_joueur(joueur);
}
/* sauvegarde la partie */
void save(board_t p, player_t* players) {
	FILE* f;
	size_t str_size;
	f = fopen(SAVE_FILENAME, "wb");
	if (f == NULL) {
		fprintf(stderr, "Impossible d'ecrire le fichier de sauvegarde...");
		exit(1);
	}
	fwrite(&p, sizeof(board_t), 1, f);
	for (int i = 0; i < p.nb_players; i++) {
		fwrite(&players[i], sizeof(player_t), 1, f);
		str_size = strlen(players[i].name);
		fwrite(&str_size, sizeof(size_t), 1, f);
		fwrite(players[i].name, sizeof(char), str_size, f);
	}
	fclose(f);
	printf("Sauvegarde effectue !\n");
	system("pause");
}
/* charge une partie */
Game_t load_game() {
	FILE* f;
	Game_t game;
	board_t p;
	player_t* players = NULL;
	size_t str_size;
	f = fopen(SAVE_FILENAME, "rb");
	if (f == NULL) {
		fprintf(stderr, "Fichier introuvable...");
		exit(1);
	}
	fread(&p, sizeof(board_t), 1, f);
	players = (player_t*)calloc(p.nb_players, sizeof(player_t));
	for (int i = 0; i < p.nb_players; i++) {
		fread(&players[i], sizeof(player_t), 1, f);
		fread(&str_size, sizeof(size_t), 1, f); // je lis la taille de la chaine de caracteres
		players[i].name = (char*)malloc(sizeof(char) * str_size + 1);
		fread(players[i].name, sizeof(char), str_size, f);
		if (players[i].name) {
			players[i].name[str_size] = '\0'; // delimite par un \0 sinon depassement du tableau
		}
	}
	fclose(f);
	game.players = players;
	game.p = p;
	return game;
}
