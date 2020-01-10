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

#define SAVE_FILENAME "save.dat"

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
    SAVE_S,
    LOAD,
    QUIT
};

/*position des chevaux*/
typedef struct chevaux_s {
    int couleur;
    int numero;
    int position;
    int pos_pyrd;
    char name_case[4];
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
    int is_playing;
    chevaux_t tmp_case[4];
    chevaux_t chevaux[4];
} joueur_t;

typedef struct plateau_s {
    chevaux_t board[LEN_BOARD];
    chevaux_t rouge_f[LEN_BOARD_FINAL];
    chevaux_t bleu_f[LEN_BOARD_FINAL];
    chevaux_t jaune_f[LEN_BOARD_FINAL];
    chevaux_t vert_f[LEN_BOARD_FINAL];
    int nb_joueurs;
} plateau_t;

typedef struct Game_s {
    joueur_t* joueurs;
    plateau_t p;
} Game_t;

int jet_des();
char* get_input();
joueur_t init_joueur(int couleur, int num_j, int sortie_pos, int is_pnj, char* name);
void affiche_etat_joueur(joueur_t* j);
int ingame_choice();
int fsave_exists(const char* file_name);
int is_collide(plateau_t p, chevaux_t horse, int pos);
void print_ecuries(joueur_t* j);
void eat_horse(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos); 
int choose_cheval(joueur_t* j);
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
void go_back(plateau_t* p, joueur_t* current_joueur, chevaux_t cheval_choosen, joueur_t* j_eat, int pos);
void move_prd(plateau_t* p, joueur_t* current_joueur, chevaux_t cheval_choosen);
joueur_t* check_who_start(joueur_t* joueurs, int nb_joueurs);
void move_horse(plateau_t* p, chevaux_t* horse, joueur_t* current_joueur, int pos, chevaux_t tmp);
void cls();
int choice_replay();
void affiche_plateau(plateau_t p, joueur_t* j, chevaux_t horse);
void save(plateau_t board, joueur_t* joueurs);
Game_t load_game();
plateau_t init_plateau(int nb_joueurs);
int if_6();
int is_win(plateau_t p);
void sortie_ecurie(plateau_t* p, joueur_t* j, joueur_t* j_eat);
void Game();

#endif