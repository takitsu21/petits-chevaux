#ifndef _JEU_H
#define _JEU_H
/*evite les warnings de securite de VS*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define LEN_BOARD 57
#define LEN_BOARD_FINAL 7
#define BOARD_END -1

#define KNRM  "\033[0m"
#define KRED  "\033[1;31m"
#define KGRN  "\033[1;32m"
#define KYEL  "\033[1;33m"
#define KBLU  "\033[1;34m"

enum couleur_cheval {
    VIDE,
    ROUGE,
    BLEU,
    VERT,
    JAUNE,
};

enum color_case_start {
    V_START = 0,
    J_START = 14,
    B_START = 28,
    R_START = 42
};

/*position des chevaux*/
typedef struct chevaux_s {
    int couleur;
    int numero;
    char* name_case;
    char* cli_couleur;
} chevaux_t;

/*structure d'un joueur*/
typedef struct joueur_s {
    short num_j;
    char* nom;
    int ecurie;
    int couleur;
    int jet_des;
    chevaux_t chevaux[4];
} joueur_t;

typedef struct plateau_s {
    //char** board;
    chevaux_t board[LEN_BOARD];
    chevaux_t rouge_f[LEN_BOARD_FINAL];
    chevaux_t bleu_f[LEN_BOARD_FINAL];
    chevaux_t jaune_f[LEN_BOARD_FINAL];
    chevaux_t vert_f[LEN_BOARD_FINAL];
    int tour;
    int nb_joueurs;
} plateau_t;

int jet_des();

int char_to_int(char c);

char* get_input();

joueur_t* init_joueur(int couleur, short i, int* array_des);

char* char_to_string(char c);

int ingame_choice();

char int_couleur_to_char(int couleur);

chevaux_t init_chevaux(int couleur, int numero, char* Kcouleur, char* name_case);

void desalloc_ptr(void* ptr);

int* process_board_idx(plateau_t p, joueur_t* j, int jet_des, int base_row, int base_col);

int check_who_start(int* des, int nb_joueurs);

void cls();

void affiche_plateau(plateau_t p);

int check_cheval(plateau_t p, int _case);

int is_vide(plateau_t p, int _case);

void modif_case(plateau_t p, joueur_t* j, int row, int col);

void tour_suivant(plateau_t p);

void manger_cheval(plateau_t p, joueur_t* j, joueur_t* j_manger, int _case);

void save(plateau_t board, char* path);

plateau_t load(char* path);

plateau_t init_plateau(int nb_joueurs, int tour);

int is_win(plateau_t p);

void sortie_ecurie(plateau_t p, joueur_t* j);

void affiche_etat_joueur(joueur_t* j);

int match_case_start(int couleur);

void game();

#endif