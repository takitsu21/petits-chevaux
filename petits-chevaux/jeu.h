#ifndef _JEU_H
#define _JEU_H
/*evite les warnings de securite de VS*/
/*#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_NAME 256

#define LEN_BOARD 56
#define LEN_BOARD_FINAL 7
#define ROWS 15

#define R_EC_SORTIE 1
#define Y_EC_SORTIE 15
#define G_EC_SORTIE 29
#define B_EC_SORTIE 43

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

enum couleur_cheval {
    VIDE,
    ROUGE,
    BLEU,
    VERT,
    JAUNE,
    WIN
};

enum ingame_mode {
    JET_DES = 1,
    SAVE
};

enum mode {
    NEW_GAME = 1,
    LOAD,
    QUIT
};

/*position des chevaux*/
typedef struct chevaux_s {
    int couleur;
    int numero;
    int position;
    int pos_pyrd;
    char* name_case;
    int num_j;
} chevaux_t;

/*structure d'un joueur*/
typedef struct joueur_s {
    int num_j;
    char* nom;
    int ecurie;
    int couleur;
    int jet_des;
    int sortie_pos;
    int on_board;
    int is_pnj;
    chevaux_t pyrd[LEN_BOARD_FINAL];
    chevaux_t tmp_case[4];
    chevaux_t chevaux[4];
} joueur_t;

typedef struct plateau_s {
    chevaux_t board[LEN_BOARD];
    chevaux_t rouge_f[LEN_BOARD_FINAL];
    chevaux_t bleu_f[LEN_BOARD_FINAL];
    chevaux_t jaune_f[LEN_BOARD_FINAL];
    chevaux_t vert_f[LEN_BOARD_FINAL];
    joueur_t* tour;
    int nb_joueurs;
} plateau_t;

int jet_des();
char* get_input();
joueur_t* init_joueur(int couleur, int num_j, int sortie_pos, int is_pnj);
void affiche_etat_joueur(joueur_t* j);
int ingame_choice();
int is_collide(plateau_t* p, chevaux_t* horse, int pos);
void print_ecuries(joueur_t* j);
void eat_horse(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos); int choose_cheval(joueur_t* j);
chevaux_t* horses_in_ecurie(joueur_t* j);
int choose_cheval_ecurie(joueur_t* j);
chevaux_t* horses_on_board(joueur_t* j);
chevaux_t init_chevaux(int couleur, int numero, char* name_case, int num_j);
void print_elems(int n, ...);
int start_choice();
void start_ascii();
int get_nb_joueurs();
int ingame_choice();
void desalloc_ptrs(void* arg, ...);
int check_couleur_sortie(int couleur);
joueur_t* check_who_start(joueur_t** des, int nb_joueurs);
void move_horse(plateau_t* p, chevaux_t* horse, joueur_t* current_joueur, int pos, chevaux_t tmp);
void cls();
int choice_replay();
void affiche_plateau(plateau_t p, joueur_t* j);
void save(plateau_t* board, joueur_t* j);
void load();
plateau_t init_plateau(int nb_joueurs, joueur_t* tour);
int if_6();
int is_win(plateau_t p);
joueur_t* get_joueur_by_couleur(int _couleur, joueur_t* j1, joueur_t* j2, joueur_t* j3, joueur_t* j4);
void sortie_ecurie(plateau_t* p, joueur_t* j, chevaux_t horse, joueur_t* j_eat, int pos); void affiche_etat_joueur(joueur_t* j);
void game();

#endif