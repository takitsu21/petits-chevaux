#ifndef _JEU_H
#define _JEU_H
/*evite les warnings de securite de VS*/
// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOM 100
#define MAX_BOARD 81

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

typedef struct joueur_s {
    char nom[MAX_NOM];
    int ecurie;
    int couleur;
    int jet_des;
} joueur_t;

typedef struct plateau_s {
    char board[MAX_BOARD];
    int tour;
    int nb_joueurs;
} plateau_t;

int jet_des();

int char_to_int(char c);

joueur_t* init_joueur(int couleur, int i, int* array_des);

char* char_to_string(char c);

char int_couleur_to_char(int couleur);

void init_game();

int check_who_start(int* des, int nb_joueurs);

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