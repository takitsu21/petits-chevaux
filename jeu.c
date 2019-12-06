#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

int jet_des (void) {
	srand(time(NULL));
	return (rand() % (7 - 1) + 1);
}


