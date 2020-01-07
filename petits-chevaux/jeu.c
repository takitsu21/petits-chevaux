#include "jeu.h"

/* jet de d�s de 1 � 6 */
int jet_des() {
	srand(time(NULL));
	int my_rand = rand() % 6 + 1;
	//printf("Vous avez fait %d avec le des", my_rand);
	return (my_rand);
}

/*nettoie le terminal*/
void cls() {
	system("cls");
}

/*recupere les input dynamiquement*/
char* get_input() {
	int c;
	char* input = (char*)malloc(sizeof(char) * MAX_NAME);
	while (scanf(" %[^\n]", input) != 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Erreur, reessayer : ");
	}
	input[MAX_NAME - 1] = '\0';
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

int start_choice() {
	int n;
	printf("Bienvenue dans le jeu des petits chevaux\nChoississez parmis les 3 propositions suivantes :\n"\
		"          [1] Nouvelle partie\n"\
		"          [2] Charger une partie\n"
		"          [3] Quitter\n");
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || !(n >= 1 && n <= 3) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"          [1] Nouvelle partie\n"\
			"          [2] Charger une partie\n"
			"          [3] Quitter\n");
		printf("Choix :");

	}
	return n;
}

int choice_replay() {
	int n;
	printf("Encore a vous ! Vous avez fait 6\n");
	printf("Faites un choix :\n"\
		"          [1] Jeter les des\n"\
		"          [2] Sortie cheval de l'ecurie\n"\
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

void start_ascii() {
	printf("______    _   _ _          _                                \n");
	printf("| ___ \\  | | (_| |        | |                               \n");
	printf("| |_/ ___| |_ _| |_    ___| |__   _____   ____ _ _   ___  __\n");
	printf("|  __/ _ | __| | __|  / __| '_ \\ / _ \\ \\ / / _` | | | \\ \\/ /\n");
	printf("| | |  __| |_| | |_  | (__| | | |  __/\\ V | (_| | |_| |>  < \n");
	printf("\\_|  \\___|\\__|_|\\__|  \\___|_| |_|\\___| \\_/ \\__,_|\\__,_/_/\\_\\\n\n");
}

int has_horse_outside(joueur_t* j) {
	for (int i = 0; i < 4; i++) {
		if (j->chevaux[i].position != -1) {
			return 1;
		}
	}
	return 0;
}

chevaux_t* horses_on_board(joueur_t* j) {
	chevaux_t* horses_outside = NULL;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (j->chevaux[i].position != -1) {
			horses_outside = realloc(horses_outside, (count + 1) * sizeof(chevaux_t));
			horses_outside[count] = j->chevaux[i];
			count++;
		}
	}
	if (horses_outside != NULL) {
		return horses_outside;
	}
	return NULL;
}

int choose_cheval(joueur_t* j) {
	int n;
	chevaux_t* horses_available = horses_on_board(j);
	printf("Choississez votre cheval a utiliser :\n");
	for (int i = 0; i < j->on_board; i++) {
		printf("		[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
	}
	printf("Choix : ");
	while (scanf(" %d", &n) != 1 || is_valid_input(horses_available, n, j->ecurie) != 1) {
		while (getchar() != '\n');
		printf("Choississez votre cheval a utiliser :\n");
		for (int i = 0; i < j->on_board; i++) {
			printf("		[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
		}
		printf("Choix : ");
	}
	return n-1;
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
	for (int i = 0; i < ecurie; i++) {
		if (horses_available[i].numero == n) {
			printf("%s %d\n", horses_available[i].name_case, n);
			system("pause");
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
		while (getchar() != '\n' );
		printf("Choississez votre cheval a utiliser :\n");
		for (int i = 0; i < j->ecurie; i++) {
			if (horses_available[i].position == -1) {
				printf("		[%d] %s\n", horses_available[i].numero, horses_available[i].name_case);
			}
		}
		printf("Choix : ");
	}
	return n-1;
}

joueur_t* get_joueur_by_couleur(int _couleur, joueur_t* j1, joueur_t* j2, joueur_t* j3, joueur_t* j4) {

	switch (_couleur)
	{
	case ROUGE:
		return j1;
	case BLEU:
		return j2;
	case VERT:
		return j3;
	case JAUNE:
		return j4;
	default:
		return NULL;
	}
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
	double r_choice;
	srand(time(NULL));
	while (1) {
		r_choice = rand() %( 4 + 1);
		//printf("%d", r_choice);
		//system("pause");
		if (is_valid_input(horses, r_choice, j->ecurie)) {
			return r_choice - 1;
		}
	}
	Sleep(200);
}

void sortie_ecurie_s(plateau_t* p, joueur_t* j) {
	chevaux_t horse;
	if (j->is_pnj) {
		horse = j->chevaux[random_choice_pnj(j, horses_in_ecurie(j), j->ecurie)];
	}
	else {
		horse = j->chevaux[choose_cheval_ecurie(j)];
	}
	horse.position = j->sortie_pos;

	j->chevaux[horse.numero - 1] = horse;
	j->tmp_case[j->chevaux[horse.numero - 1].numero - 1] = p->board[j->sortie_pos];
	p->board[j->sortie_pos] = horse;
	j->ecurie -= 1;
	j->on_board += 1;

}

void sortie_ecurie(plateau_t* p, joueur_t* j, chevaux_t horse, joueur_t* j_eat, int pos) {
	if (is_collide(&p, &horse, j->sortie_pos) == -1) {
		printf("Ressayer\n");
		system("pause");
	}
	else if (is_collide(&p, &horse, j->sortie_pos) == 1) {
		j->on_board += 1;
		j->ecurie -= 1;
		j_eat->chevaux[p->board[pos].numero - 1].position = -1;
		j_eat->on_board -= 1;
		j_eat->ecurie += 1;
		j->tmp_case[horse.numero - 1] = j_eat->tmp_case[j_eat->chevaux[p->board[pos].numero - 1].numero - 1];
		j->chevaux[horse.numero - 1].position = pos;
		p->board[pos] = j->chevaux[horse.numero - 1];
	}
	else {
		horse.position = j->sortie_pos;
		j->chevaux[horse.numero - 1] = horse;
		j->tmp_case[j->chevaux[horse.numero - 1].numero-1] = p->board[j->sortie_pos];
		p->board[j->sortie_pos] = horse;
		j->ecurie -= 1;
		j->on_board += 1;
	}

}
//get_joueur_by_couleur(p.board[pos].couleur, j1, j2, j3, j4)
void eat_horse(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos) {
	chevaux_t old_case = current_joueur->tmp_case[horse.numero - 1];
	int old_pos = horse.position;
	j_eat->chevaux[p->board[pos].numero - 1].position = -1;
	j_eat->on_board -= 1;
	j_eat->ecurie += 1;
	current_joueur->tmp_case[horse.numero - 1] = j_eat->tmp_case[j_eat->chevaux[p->board[pos].numero - 1].numero-1];
	current_joueur->chevaux[horse.numero - 1].position = pos;
	p->board[pos] = current_joueur->chevaux[horse.numero-1];
	p->board[old_pos] = old_case;	
	
}

int is_collide(plateau_t* p, chevaux_t* horse, int pos) {
	if (p->board[pos].position >= 0 && p->board[pos].position < 57 && horse->position != -1) {
		if (p->board[pos].couleur != horse->couleur) {
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
	int accepted = is_elligible_prd(j, pos);
	if (accepted == 0) {
		return first_stair;
	}
	else if (accepted == -1) {
		return pos;
	}
	if (first_stair == 0) {
		first_stair += 56;
		pos += 56;
	}
	new_pos = first_stair - (pos - first_stair);
	return new_pos;
}

int is_elligible_prd(joueur_t* j, int pos) {
	int first_stair = j->sortie_pos - 1;
	int tour_complet = first_stair - pos;
	printf("pos = %d first_stair = %d\n", pos, first_stair);
	//system("pause");
	if (tour_complet <= 6) {
		if (pos == first_stair) {
			return 0; // elligible
		}
		else if (pos > first_stair) {
			return 1; // superieur
		}
	}
	return -1; // inferieur
}

void move_horse(plateau_t* p, chevaux_t* horse, joueur_t* current_joueur, int pos, chevaux_t tmp) {
	pos = (horse->position + current_joueur->jet_des) % 56;
	p->board[pos] = current_joueur->chevaux[horse->numero - 1];
	p->board[horse->position] = current_joueur->tmp_case[horse->numero - 1];
	current_joueur->tmp_case[horse->numero-1] = tmp;
	horse->position = pos;
}

void pnj_plays(plateau_t* p, joueur_t* j, joueur_t** joueurs) {
	chevaux_t tmp;
	int pos;
	int if_6_res;
	int choice;
	chevaux_t horse;
	j->jet_des = jet_des();

	if (j->on_board) {
		choice = random_choice_pnj(j, horses_on_board(j), j->ecurie);
		horse = j->chevaux[choice];
		pos = (horse.position + j->jet_des) % 56;
		tmp = p->board[pos];
		printf("Le pnj a obtenu %d\n", j->jet_des);
		//system("pause");
		if (is_elligible_prd(j, pos) == -1) {
			if (is_collide(&p, &horse, pos) == 1) {
				eat_horse(&p, j, horse, joueurs[p->board[pos].num_j - 1], pos);
				//break;
			}
			else if (is_collide(&p, &horse, pos) == -1) {
				return;
			}
			//si on a 6
			else if (is_6(j)) {
				while (j->jet_des == 6) {
					pos = (horse.position + j->jet_des) % 56;
					tmp = p->board[pos];
					if_6_res = rand() % 2 + 1;
					if (if_6_res == 1) {
						if (is_collide(&p, &horse, j->sortie_pos) == -1) {
							printf("Vous ne pouvez sortir un cheval il y a deja un de vos chevaux sur la case\n");
							system("pause");
							continue;
						}
						else if (is_collide(&p, &horse, j->sortie_pos) == 1) {
							sortie_ecurie(&p, j, j->chevaux[random_choice_pnj(j, horses_on_board(j), j->ecurie)], joueurs[p->board[pos].num_j - 1], pos);

							printf("sortie ecurie mange\n");
							system("pause");
						}
						else {
							sortie_ecurie(&p, j, j->chevaux[random_choice_pnj(j, horses_on_board(j), j->ecurie)], joueurs[p->board[pos].num_j - 1], pos);
						}

						affiche_plateau(*p, j);
						j->jet_des = jet_des();

						if (j->jet_des != 6) {
							choice = random_choice_pnj(j, horses_on_board(j), j->ecurie);
							horse = j->chevaux[choice];
							pos = (horse.position + j->jet_des) % 56;
							if (is_collide(&p, &horse, pos) == 1) {
								eat_horse(&p, j, horse, joueurs[p->board[pos].num_j - 1], pos);
							}
							else if (is_collide(&p, &horse, pos) == -1) {
								printf("Choisissez un autre cheval");
							}
							else {
								printf("Vous rejouez automatiquement\nVous avez obtenu %d\n", j->jet_des);
								system("pause");
								if (is_collide(&p, &horse, pos) == 1) {
									eat_horse(&p, j, horse, joueurs[p->board[pos].num_j - 1], pos);
								}
								else {
									move_horse(*(&p), &horse, j, pos, tmp);
								}
							}
							affiche_plateau(*p, j);
							break;
						}
						else {
							continue; // skip si un 6 n'est pas relancer sinon continue de rejouer
						}

					}
					else if (if_6_res == 2) { //choisis d'avancer de 6 cases
						tmp = p->board[pos];
						move_horse(*(&p), &horse, j, pos, tmp);

						affiche_plateau(*p, j);
						j->jet_des = jet_des();
						if (j->jet_des != 6) {
							choice = random_choice_pnj(j, horses_on_board(j), j->ecurie);
							horse = j->chevaux[choice];
							pos = (horse.position + j->jet_des) % 56;
							tmp = p->board[pos];
							printf("Vous relancer les des automatiquement\nVous avez obtenu %d\n", j->jet_des);
							move_horse(*(&p), &horse, j, pos, tmp);
							affiche_plateau(*p, j);
							break;
						}
					}
					else {
						//save()
					}
				}
			}
			else { // bouge normalement (aucun obstacle)
				move_horse(*(&p), &horse, j, pos, tmp);
			}
		}
		else if (is_elligible_prd(j, pos) == 1) {
			pos = new_pos_backward(j, pos);
			move_horse(*(&p), &horse, j, pos, tmp);
		}
		else {

		}
	}
	else if (is_6(j)) {
		sortie_ecurie_s(*(&p), j);
		while (1) {
			choice = rand() % j->ecurie + 1;
			if (is_valid_input(horses_in_ecurie(j), choice, j->ecurie)) {
				horse = j->chevaux[choice];
				break;
			}
		}
		Sleep(1500);
	}
}

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

void game() {
	start_ascii();
	int nb_joueurs;
	joueur_t* j1 = NULL;
	joueur_t* j2 = NULL;
	joueur_t* j3 = NULL;
	joueur_t* j4 = NULL;
	plateau_t p;
	
	int mode = start_choice();
	switch (mode)
	{
	case NEW_GAME:
		nb_joueurs = get_nb_joueurs();
		j1 = init_joueur(ROUGE, 1, R_EC_SORTIE, is_pnj());
		j2 = init_joueur(BLEU, 2, B_EC_SORTIE, is_pnj());
		if (nb_joueurs == 3) {
			j3 = init_joueur(VERT, 3, G_EC_SORTIE, is_pnj());
		}
		else if (nb_joueurs == 4) {
			j3 = init_joueur(VERT, 3, G_EC_SORTIE, is_pnj());
			j4 = init_joueur(JAUNE, 4, Y_EC_SORTIE, is_pnj());
		}
		if (j3 == NULL) {
			// TODO : faire spawn un pnj
			//j3 = init_joueur(VERT, 3, G_EC_SORTIE, 1);
		}
		if (j4 == NULL) {
			// TODO : faire spawn un pnj
			//j4 = init_joueur(JAUNE, 4, Y_EC_SORTIE, 1);
		}
		joueur_t* joueurs[4] = { j1, j2, j3, j4 };
		joueur_t* _tour = check_who_start(joueurs, nb_joueurs);
		joueur_t* current_joueur;
		joueur_t* j_manger;
		chevaux_t tmp;
		chevaux_t* cheval_choosen;
		int choose_idx;
		int if_6_res;
		int i = _tour->num_j-1;
		p = init_plateau(nb_joueurs, _tour);
		cls();
		//p.board[R_EC_SORTIE] = j1->chevaux[0];
		int pos;
		while (1) {
			current_joueur = _tour;
			affiche_plateau(p, current_joueur);
			printf("cj = %d\n", current_joueur->is_pnj);
			if (current_joueur->is_pnj == 1) {
				pnj_plays(&p, current_joueur, joueurs);
				i = (i + 1) % nb_joueurs;
				_tour = joueurs[i];
				Sleep(150);
				continue;
			}
			//has_horse_outside(current_joueur)
			else if (current_joueur->on_board) {
				choose_idx = choose_cheval(current_joueur);
				cheval_choosen = &current_joueur->chevaux[choose_idx];
				while (1) {
					switch (ingame_choice())
					{
					case JET_DES:
						current_joueur->jet_des = jet_des();
						pos = (cheval_choosen->position + current_joueur->jet_des) % 56;
						tmp = p.board[pos];
						printf("Vous avez fait %d\n", current_joueur->jet_des);
						system("pause");
						if (is_elligible_prd(current_joueur, pos) == -1) {
							if (is_collide(&p, cheval_choosen, pos) == 1) {
								eat_horse(&p, current_joueur, current_joueur->chevaux[choose_idx], joueurs[p.board[pos].num_j - 1], pos);
								break;
							}
							else if (is_collide(&p, cheval_choosen, pos) == -1) {
								continue;
							}
							//si on a 6
							else if (is_6(current_joueur)) {
								while (current_joueur->jet_des == 6) {
									pos = (cheval_choosen->position + current_joueur->jet_des) % 56;
									tmp = p.board[pos];
									if_6_res = if_6();
									if (if_6_res == 1) {
										if (is_collide(&p, cheval_choosen, current_joueur->sortie_pos) == -1) {
											printf("Vous ne pouvez sortir un cheval il y a deja un de vos chevaux sur la case\n");
											system("pause");
											continue;
										}
										else if (is_collide(&p, cheval_choosen, current_joueur->sortie_pos) == 1) {
											sortie_ecurie(&p, current_joueur, current_joueur->chevaux[choose_cheval_ecurie(current_joueur)], joueurs[p.board[pos].num_j - 1], pos);

											printf("sortie ecurie mange\n");
											system("pause");
										}
										else {
											sortie_ecurie(&p, current_joueur, current_joueur->chevaux[choose_cheval_ecurie(current_joueur)], joueurs[p.board[pos].num_j - 1], pos);
										}

										affiche_plateau(p, current_joueur);
										current_joueur->jet_des = jet_des();

										if (current_joueur->jet_des != 6) {
											choose_idx = choose_cheval(current_joueur);
											cheval_choosen = &current_joueur->chevaux[choose_idx];
											pos = (cheval_choosen->position + current_joueur->jet_des) % 56;
											if (is_collide(&p, cheval_choosen, pos) == 1) {
												eat_horse(&p, current_joueur, current_joueur->chevaux[choose_idx], joueurs[p.board[pos].num_j - 1], pos);
											}
											else if (is_collide(&p, cheval_choosen, pos) == -1) {
												printf("Choisissez un autre cheval");
											}
											else {
												printf("Vous rejouez automatiquement\nVous avez obtenu %d\n", current_joueur->jet_des);
												system("pause");
												if (is_collide(&p, cheval_choosen, pos) == 1) {
													eat_horse(&p, current_joueur, current_joueur->chevaux[choose_idx], joueurs[p.board[pos].num_j - 1], pos);
												}
												else {
													move_horse(&p, cheval_choosen, current_joueur, pos, tmp);
												}
											}
											affiche_plateau(p, current_joueur);
											break;
										}
										else {
											continue; // skip si un 6 n'est pas relancer sinon continue de rejouer
										}

									}
									else if (if_6_res == 2) { //choisis d'avancer de 6 cases
										tmp = p.board[pos];
										move_horse(&p, cheval_choosen, current_joueur, pos, tmp);

										affiche_plateau(p, current_joueur);
										current_joueur->jet_des = jet_des();
										if (current_joueur->jet_des != 6) {
											choose_idx = choose_cheval(current_joueur);
											cheval_choosen = &current_joueur->chevaux[choose_idx];
											pos = (cheval_choosen->position + current_joueur->jet_des) % 56;
											tmp = p.board[pos];
											printf("Vous relancer les des automatiquement\nVous avez obtenu %d\n", current_joueur->jet_des);
											move_horse(&p, cheval_choosen, current_joueur, pos, tmp);
											affiche_plateau(p, current_joueur);
											//break;
										}
									}
									else {
										//save()
									}
								}
							}
							else { // bouge normalement (aucun obstacle)
								move_horse(&p, cheval_choosen, current_joueur, pos, tmp);
								break;
							}
						}
						else if (is_elligible_prd(current_joueur, pos) == 1) {
							pos = new_pos_backward(current_joueur, pos);
							move_horse(&p, &current_joueur->chevaux[choose_idx], current_joueur, pos, tmp);
						}
						else {

						}
						break;
					case SAVE:
						//save
					case QUIT:
						exit(0);
					default:
						break;
					}
					break;
				}

			}
			else {

				switch (ingame_choice())
				{
				case JET_DES:
					
					current_joueur->jet_des = jet_des();
					if (is_6(current_joueur)) {
						sortie_ecurie_s(&p, current_joueur);
						Sleep(1500);
					}
					break;
				case SAVE:
					//save()
				case QUIT:
					exit(0);
				default:
					break;
				}
			}

			i = (i + 1) % nb_joueurs;
			_tour = joueurs[i];
		}
		break;
	case LOAD:
		//load(path);
	case QUIT:
		exit(EXIT_SUCCESS);
	default:
		break;
	}

	//system("pause");
}

joueur_t* check_who_start(joueur_t** des, int nb_joueurs) {
	int max = 0;
	joueur_t* res = (joueur_t*)malloc(sizeof(joueur_t));
	for (int i = 0; i < nb_joueurs; i++) {
		if (des[i] != NULL && des[i]->jet_des > max) {
			max = des[i]->jet_des;
			res = des[i];
		}
	}
	return res;
}

void toupper_string(const char* s) {
	while (*s++) {
		putchar(toupper(*s));
	}
}

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
joueur_t* init_joueur(int couleur, int num_j, int sortie_pos, int is_pnj) {
	joueur_t* j = (joueur_t*)malloc(sizeof(joueur_t));
	char num_chevaux[4][4] = { {"C1 "}, {"C2 "}, {"C3 "}, {"C4 "} };
	char bots_name[4][10] = { {"HAL 9000"}, {"T 1000"}, {"R2D2"}, {"T 800"} };
	j->num_j = num_j;
	printf("is_pnj = %d", is_pnj);
	if (is_pnj == 1) {
		j->nom = (char*)malloc(sizeof(char) * strlen(bots_name[num_j - 1] + 1));
		j->nom = bots_name[num_j - 1];
		printf("%s", j->nom);
	}
	else {
		printf("Nom du joueur %d : ", num_j);
		j->nom = get_input();
	}
	
	j->ecurie = 4;
	j->on_board = 0;
	j->sortie_pos = sortie_pos;
	j->couleur = couleur;
	j->jet_des = jet_des();
	j->is_pnj = is_pnj;
	//j->tmp_case;
	for (int i = 0; i < 4; i++) {
		j->chevaux[i] = init_chevaux(couleur, i + 1, num_chevaux[i], num_j);
	}
	return j;
}

chevaux_t init_chevaux(int couleur, int numero, char* name_case, int num_j) {
	chevaux_t chevaux;
	size_t len_name_case = strlen(name_case);
	chevaux.couleur = couleur;
	chevaux.numero = numero;
	chevaux.position = -1;
	chevaux.num_j = num_j;
	chevaux.pos_pyrd = 1;
	chevaux.name_case = (char*)malloc(sizeof(char) * len_name_case + 1);
	strcpy(chevaux.name_case, name_case);
	return chevaux;
}

int ingame_choice() {
	int n;
	printf("Faites un choix :\n"\
		"          [1] Jeter les des\n"\
		"          [2] Sauvegarder la partie"\
		"          [3] Quitter le jeu\nChoix : ");
	while (scanf(" %d", &n) != 1 || !(n > 0 && n < 4) == 1) {
		while (getchar() != '\n');
		cls();
		start_ascii();
		printf("Choix non valide\nFaites un choix :\n"\
			"          [1] Jeter les des\n"\
			"          [2] Sauvegarder la partie\n"\
			"          [3] Quitter le jeu\nChoix : ");
	}
	return n;
}

/* initialise le plateau de jeu*/
plateau_t init_plateau(int nb_joueurs, joueur_t* tour) {
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
	p.tour = tour;
	return p;
}

void tour_suivant(plateau_t p) {
	//p.tour += 1 % p.nb_joueurs;
}


int est_mangeable(plateau_t p, joueur_t* j, int num_cheval, int pos_to_go) {
	if (j->couleur != p.board[pos_to_go].couleur) {
		return 1;
	}
	return 0;
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

int is_6(joueur_t* j) {
	return j->jet_des == 6;
}


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
		else {
			printf(KNRM "%s", board_case.name_case);
		}
	}
	va_end(ap);
}

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
void affiche_plateau(plateau_t p, joueur_t* j) {
	int tmp; //utiliser pour les cases lateral
	int show_couleur = 0;
	int start_idx = 0;
	int i = 0;
	int last_idx = LEN_BOARD-1;
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
	affiche_etat_joueur(j);
}

void save(plateau_t board, char* path) {}

plateau_t load(char* path) {}
