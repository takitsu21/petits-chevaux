#ifndef _JEU_H
#define _JEU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NOM 100
#define MAX_BOARD 81

enum couleur_cheval {
    ROUGE,
    BLEU,
    VERT,
    JAUNE,
    VIDE
};

typedef struct joueur_s {
    char nom[MAX_NOM];
    int ecurie;
    int couleur;
} joueur_t;

typedef struct cheval_s {
    int couleur;
    int numero;
} cheval_t;

typedef struct plateau_s {
    cheval_t board[MAX_BOARD];
    int tour;
    int nb_joueur;
} plateau_t;

int jet_des();

joueur_t* init_joueur(int couleur, int i);

char* int_couleur_to_char(int couleur);

int char_to_couleur(char* s);

void affiche_plateau(plateau_t board);

int check_cheval(plateau_t board, int _case);

void init_game();

int is_vide(plateau_t board, int _case);

void modif_case(plateau_t board, int _case);

void tour_suivant(plateau_t board);

void ajouter_cheval(plateau_t board, joueur_t* j);

void manger_cheval(plateau_t board, joueur_t* j, int _case);

void save(plateau_t board, char* path);

plateau_t load(char* path);

int is_win(plateau_t board);

void affiche_etat_joueur(joueur_t* j);

#endif