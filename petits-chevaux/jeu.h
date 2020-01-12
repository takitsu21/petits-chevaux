#ifndef _JEU_H
#define _JEU_H
/*evite les warnings de securite de VS
https://www.journaldunet.fr/web-tech/developpement/1202787-comment-retirer-les-alertes-de-securite-crt-secure-no-warnings-dans-visual-studio/ */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME        512 // taille du nom maximum
#define LEN_BOARD       56 // taille du plateau principal
#define LEN_BOARD_FINAL 7 // taille des pyramides
#define ROWS            15 // lignes du plateau
#define R_EC_OUT        1 // position de la sortie de l'ecurie rouge
#define Y_EC_OUT        15 // position de la sortie de l'ecurie jaune
#define G_EC_OUT        29 // position de la sortie de l'ecurie vert
#define B_EC_OUT        43 // position de la sortie de l'ecurie bleu
#define SAVE_FILENAME   "save.dat" // nom du fichier de sauvegarde
// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define KNRM            "\x1B[0m" // couleur normal du terminal
#define KRED            "\x1B[31m" // couleur rouge du terminal
#define KGRN            "\x1B[32m" // couleur verte du terminal
#define KYEL            "\x1B[33m" // couleur jaune du terminal
#define KBLU            "\x1B[34m" // couleur bleu du terminal

// representation des couleurs des chevaux
enum horse_colors {
    VIDE, // case vide
    RED,
    BLUE,
    GREEN,
    YELLOW,
};
// mode de jeu pendant la partie
enum ingame_mode {
    ROLL_DICE = 1,
    SAVE
};
// mode jeu
enum mode {
    NEW_GAME = 1,
    RULES,
    QUIT
};

/*position des chevaux*/
typedef struct horse_s {
    int  color; // couleur du cheval
    int  numero; // numero du cheval
    int  position; // position du cheval
    int  pos_pyrd; // position dans la pyramide du cheval
    char name_case[4]; // nom du cheval
    int  num_j; // numero du joueur du cheval
} horse_t;

/*structure d'un joueur*/
typedef struct player_s {
    int       num_j; // numero du joueur
    char*     name; // nom du joueur
    int       ecurie; // nombre de chevaux dans l'ecurie
    int       color; // couleur du joueur
    int       roll_dice; // jet de des
    int       out_pos; // position de sortie de l'ecurie en fonction de la couleur
    int       on_board; // nombre de chevaux sur le plateau, 0 si aucun
    int       is_pnj; // 1 si le joueur est un pnj, 0 sinon
    int       is_playing; // 1 si le joueur joue actuellement, 0 sinon
    horse_t   tmp_case[4]; // cases temporaires pour inverser les cases du plateau
    horse_t   horse[4]; // chevaux du joueur
} player_t;
/* structure de mes plateaux pour gerer les chevaux du terrain*/
typedef struct board_s {
    horse_t board[LEN_BOARD]; // plateau principal
    horse_t red_final[LEN_BOARD_FINAL]; // pyramide rouge
    horse_t blue_final[LEN_BOARD_FINAL]; // pyramide bleu
    horse_t yellow_final[LEN_BOARD_FINAL]; // pyramide jaune
    horse_t green_final[LEN_BOARD_FINAL]; // pyramide verte
    int     nb_players; // nombre de joueurs de la partie
} board_t;
/* sert a sauvegarder ma partie */
typedef struct Game_s {
    player_t* players; // tout les joueurs
    board_t p; // plateau
} Game_t;

int roll_dice(int max);
char* get_input();
player_t init_player(int color, int num_j, int sortie_pos, int is_pnj, char* name);
void show_state_player(player_t* j);
int ingame_choice();
int fsave_exists(const char* file_name);
int is_collide(board_t p, horse_t horse, int pos);
void print_ecuries(player_t* j);
int is_pnj();
int is_6(player_t* p);
int is_valid_input(horse_t* horses_available, int n, int ecurie);
void eat_horse(board_t* p, player_t* current_player, horse_t horse, player_t* p_eat, int pos); 
int choose_horse(player_t* j);
horse_t* horses_in_ecurie(player_t* j);
int choose_horse_ecurie(player_t* j);
horse_t* horses_on_board(player_t* j);
horse_t init_horses(int color, int numero, char* name_case, int num_j);
void print_elems(int n, ...);
int start_choice();
int is_elligible_pyrd(player_t* j, horse_t horse, int pos);
int new_pos_backward(player_t* j, int pos);
void start_ascii();
void desalloc_players(player_t* players, int nb_players);
int get_nb_players();
void go_back(board_t* p, player_t* current_player, horse_t horse, player_t* p_eat, int pos);
void move_prd(board_t* p, player_t* current_player, horse_t horse, player_t* players);
player_t* check_who_start(player_t* players, int nb_players);
void move_horse(board_t* p, horse_t horse, player_t* current_player, int pos, horse_t tmp);
void cls();
void print_last_case(int color, horse_t horse);
int choice_load();
int choice_replay();
void show_board(board_t p, player_t* j, horse_t horse);
void save(board_t p, player_t* players);
Game_t load_game();
board_t init_board(int nb_players);
player_t* current_turn(board_t p, player_t* players);
void ia(board_t* p, player_t* current_player, player_t* players);
void sortie_ecurie(board_t* p, player_t* j, player_t* p_eat);
void Game();

#endif