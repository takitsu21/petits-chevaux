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
#include <windows.h>

#define LEN_BOARD 57
#define LEN_BOARD_FINAL 7
#define BOARD_END -1
#define ROWS 15

#define R_EC_SORTIE 1
#define G_EC_SORTIE 15
#define Y_EC_SORTIE 29
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



/*position des chevaux*/
typedef struct chevaux_s {
    int couleur;
    int numero;
    int position;
    char* name_case;
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

char* get_input();

joueur_t* init_joueur(int couleur, short i, int* array_des);

int ingame_choice();

chevaux_t init_chevaux(int couleur, int numero, char* name_case);

void print_elems(int n, ...);

int start_choice();

int get_nb_joueurs();

int ingame_choice();

void desalloc_ptrs(void* arg, ...);

int check_couleur_sortie(int couleur);

int check_who_start(int* des, int nb_joueurs);

void cls();

void affiche_plateau(plateau_t p);

int est_mangeable(plateau_t p, joueur_t* j, int num_cheval, int pos_to_go);

void modif_case(plateau_t p, joueur_t* j, int num_cheval);

void tour_suivant(plateau_t p);

void manger_cheval(plateau_t p, joueur_t* j, joueur_t* j_manger, int _case);

void save(plateau_t board, char* path);

plateau_t load(char* path);

plateau_t init_plateau(int nb_joueurs, int tour);

int is_win(plateau_t p);

void sortie_ecurie(plateau_t p, joueur_t* j);

void affiche_etat_joueur(joueur_t* j);


void game();

#endif