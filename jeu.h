#ifndef _JEU_H
#define _JEU_H

#define NB_CASE_BOARD 56
#define PLAYER1 0
#define PLAYER2 1
#define PLAYER3 2
#define PLAYER4 3
#define MAX_NOM 50

struct joueur
{
    char nom[50];
    int ecurie;
    int nb_chevaux_restant;
    int couleur;
    // char* board;
    // int jet_des;
};

typedef struct joueur Joueur;

int jet_des(void);

void affiche_player_stats(Joueur j);

void affiche_player_board(Joueur j);

void init_game(Joueur j1, Joueur j2, Joueur j3, Joueur j4);

#endif