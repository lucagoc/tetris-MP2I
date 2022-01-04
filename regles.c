#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


const int NBLINES = 22;
const int NBCOLUMNS = 10;

const bool DEBUG_MODE = false;


/*Cette fonction permet de vérifier si le joueur n'a pas perdu, c'est-à-dire si aucun bloc ne touche la ligne au dessus de la grille une fois placé.*/
void isEndgame(int mainGrid[NBLINES][NBCOLUMNS],bool* inGame){
    for(int i = 0; i < NBCOLUMNS ; i++){
        if(mainGrid[1][i] != 0){
            *inGame = false;
        }
    }
}

/* Définit le délai de descente en fonction de la difficulté. */
int set_difficulty(int difficulty){
    int time_cycle;
    switch(difficulty){
        case 1:
            time_cycle=900;
            break;
        case 2:
            time_cycle=600;
            break;
        case 3:
            time_cycle=300;
            break;
        case 4:
            time_cycle=150;
            break;

    };
    return time_cycle;
}

/* Définit le délai de placement en fonction de la difficulté. */
int set_delay(int difficulty){
    int delay;
    switch(difficulty){
        case 1:
            delay=700;
            break;
        case 2:
            delay=500;
            break;
        case 3:
            delay=300;
            break;
        case 4:
            delay=100;
            break;

    };
    return delay;
}

/* Renvoie le nombre de points à chaque ligne remplie en fct.*/
int set_points_per_line(int difficulty){
    int points_per_line;
    switch(difficulty){
        case 1:
            points_per_line=4 ;
            break;
        case 2:
            points_per_line=10;
            break;
        case 3:
            points_per_line=40;
            break;
        case 4:
            points_per_line=100;
            break;

    };
    return points_per_line;
}
