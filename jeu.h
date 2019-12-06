#ifndef _JEU_H
#define _JEU_H

#define PLAYER1 0
#define PLAYER2 1
#define PLAYER3 2
#define PLAYER4 3

struct joueur
{
    int nb_chevaux;

};

typedef struct joueur Joueur;

int jetDes (void);

#endif