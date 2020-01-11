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
#include <windows.h>


#define MAX_NAME        512 // taille du nom maximum
#define LEN_BOARD       56 // taille du plateau principal
#define LEN_BOARD_FINAL 7 // taille des pyramides
#define ROWS            15

// position de la sortie de l'ecurie de chaque couleurs
#define R_EC_SORTIE 1
#define Y_EC_SORTIE 15
#define G_EC_SORTIE 29
#define B_EC_SORTIE 43

#define SAVE_FILENAME "save.dat"

// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

// representation des couleurs des chevaux
enum couleur_cheval {
    VIDE, // case vide
    ROUGE,
    BLEU,
    VERT,
    JAUNE,
};
// mode de jeu pendant la partie
enum ingame_mode {
    JET_DES = 1,
    SAVE
};
// mode jeu
enum mode {
    NEW_GAME = 1,
    RULES,
    QUIT
};

/*position des chevaux*/
typedef struct chevaux_s {
    int  couleur; // couleur du cheval
    int  numero; // numero du cheval
    int  position; // position du cheval
    int  pos_pyrd; // position dans la pyramide du cheval
    char name_case[4]; // nom du cheval
    int  num_j; // numero du joueur du cheval
} chevaux_t;

/*structure d'un joueur*/
typedef struct joueur_s {
    int       num_j; // numero du joueur
    char*     nom; // nom du joueur
    int       ecurie; // nombre de chevaux dans l'ecurie
    int       couleur; // couleur du joueur
    int       jet_des; // jet de des
    int       sortie_pos; // position de sortie de l'ecurie en fonction de la couleur
    int       on_board; // 1 s'il y a un cheval sur le terrain, 0 sinon
    int       is_pnj; // 1 si le joueur est un pnj, 0 sinon
    int       is_playing; // 1 si le joueur joue actuellement, 0 sinon
    chevaux_t tmp_case[4]; // case temporaire pour inverser les cases du plateau
    chevaux_t chevaux[4]; // chevaux du joueur
} joueur_t;
/* structure de mes plateaux pour gerer les chevaux du terrain*/
typedef struct plateau_s {
    chevaux_t board[LEN_BOARD]; // plateau principal
    chevaux_t rouge_f[LEN_BOARD_FINAL]; // pyramide rouge
    chevaux_t bleu_f[LEN_BOARD_FINAL]; // pyramide bleu
    chevaux_t jaune_f[LEN_BOARD_FINAL]; // pyramide jaune
    chevaux_t vert_f[LEN_BOARD_FINAL]; // pyramide verte
    int       nb_joueurs; // nombre de joueurs de la partie
} plateau_t;
/* sert a sauvegarder ma partie */
typedef struct Game_s {
    joueur_t* joueurs; // tout les joueurs
    plateau_t p; // plateau
} Game_t;

int jet_des();
char* get_input();
joueur_t init_joueur(int couleur, int num_j, int sortie_pos, int is_pnj, char* name);
void affiche_etat_joueur(joueur_t* j);
int ingame_choice();
int fsave_exists(const char* file_name);
int is_collide(plateau_t p, chevaux_t horse, int pos);
void print_ecuries(joueur_t* j);
int is_pnj();
void eat_horse(plateau_t* p, joueur_t* current_joueur, chevaux_t horse, joueur_t* j_eat, int pos); 
int choose_horse(joueur_t* j);
chevaux_t* horses_in_ecurie(joueur_t* j);
int choose_horse_ecurie(joueur_t* j);
chevaux_t* horses_on_board(joueur_t* j);
chevaux_t init_chevaux(int couleur, int numero, char* name_case, int num_j);
void print_elems(int n, ...);
int start_choice();
int is_elligible_prd(joueur_t* j, chevaux_t horse, int pos);
int new_pos_backward(joueur_t* j, int pos);
void start_ascii();
void desalloc_joueurs(joueur_t* joueurs, int nb_joueurs);
int get_nb_joueurs();
void go_back(plateau_t* p, joueur_t* current_joueur, chevaux_t cheval_choosen, joueur_t* j_eat, int pos);
void move_prd(plateau_t* p, joueur_t* current_joueur, chevaux_t cheval_choosen, joueur_t* joueurs);
joueur_t* check_who_start(joueur_t* joueurs, int nb_joueurs);
void move_horse(plateau_t* p, chevaux_t horse, joueur_t* current_joueur, int pos, chevaux_t tmp);
void cls();
void print_last_case(int couleur, chevaux_t horse);
int choice_load();
int choice_replay();
void affiche_plateau(plateau_t p, joueur_t* j, chevaux_t horse);
void save(plateau_t p, joueur_t* joueurs);
Game_t load_game();
plateau_t init_plateau(int nb_joueurs);
int if_6();
joueur_t* current_turn(plateau_t p, joueur_t* joueurs);
int is_collide_prd(plateau_t p, chevaux_t horse);
void ia(plateau_t* p, joueur_t* current_joueur, joueur_t* joueurs);
void sortie_ecurie(plateau_t* p, joueur_t* j, joueur_t* j_eat);
void Game();

#endif