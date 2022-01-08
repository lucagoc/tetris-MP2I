#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ncurses.h>

#include "header/tetrimino.h"
#include "header/gameUI.h"

const int NBLINES = 22;
const int NBCOLUMNS = 10;

/* Définit les propriétés du jeu en fonction de la difficulté choisie. */
void setDifficulty(int difficulty, int* speedCycle){

    assert(difficulty != -1);  // Si la difficulté n'est pas définie.

    if (difficulty == 0) *speedCycle = 900;
    else if (difficulty == 1) *speedCycle = 600;
    else if (difficulty == 2) *speedCycle = 300;
    else *speedCycle = 150;

    return;
}

/* Vérifie si le haut de la grille est plein */
bool isGridfull(int mainGrid[NBLINES][NBCOLUMNS]){
    for(int i = 0; i < NBCOLUMNS ; i++){
        if(mainGrid[1][i] != 0){
            return true;
        }
    }
    return false;
}

/* Calcul le nombre de points à ajouter au Score. */
void scoring(int nbLinesfull, int difficulty, int* score){

    int pointsPerline;
    float nbLinescoef;

    pointsPerline = (difficulty)* 40 + 40;
    nbLinescoef = ((nbLinesfull-1)*0.4+1);

    *score += pointsPerline * nbLinesfull;  // Ajout du score.

    return;
}


/* Permet d'échanger le tetrimino dans le jeu et celui dans l'inventaire */
void switchInventory(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int* tetriminoID, int* inventory){

    if (*inventory == 0){   // Cas inventaire vide
        *inventory = *tetriminoID;
        initGrid(mobileGrid);
        setRandom(tetriminoID);
        genTetrimino(mobileGrid, *tetriminoID);

    } else {                // Cas normal
        int tmp = *inventory;
        *inventory = *tetriminoID;
        initGrid(mobileGrid);
        *tetriminoID = tmp;
        genTetrimino(mobileGrid, tmp);
    }

    return;
}

/* Exprime depuis combien de temps le jeu s'est écoulé */
int timer(int timeStarted){

    time_t timeNow = time(NULL);
    int timeElapsed = (timeNow - timeStarted);

    return timeElapsed;
}