#ifndef _JEU_H
#define _JEU_H
/*evite les warnings de securite de VS*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define LEN_BOARD 82
#define ROWS 16

#define KNRM  "\033[0m"
#define KRED  "\033[1;31m"
#define KGRN  "\033[1;32m"
#define KYEL  "\033[1;33m"
#define KBLU  "\033[1;34m"

enum couleur_cheval {
    ROUGE,
    BLEU,
    VERT,
    JAUNE,
    VIDE
};

enum color_case_start {
    V_START = 0,
    J_START = 14,
    B_START = 28,
    R_START = 42
};

typedef struct chevaux_s {
    int C1;
    int C2;
    int C3;
    int C4;
} chevaux_t;

typedef struct joueur_s {
    char* nom;
    int ecurie;
    int couleur;
    int jet_des;
    //chevaux_t chevaux;
} joueur_t;



typedef struct plateau_s {
    char** board;
    int tour;
    int nb_joueurs;
} plateau_t;

int jet_des();

int char_to_int(char c);

char* get_input();

joueur_t* init_joueur(int couleur, int i, int* array_des);

char* char_to_string(char c);

char int_couleur_to_char(int couleur);

void init_game();

void desalloc_ptr(void* _args);

int check_who_start(int* des, int nb_joueurs);

void cls();

void affiche_plateau(plateau_t p);

int check_cheval(plateau_t p, int _case);

int is_vide(plateau_t p, int _case);

void modif_case(plateau_t p, int _case, joueur_t j);

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