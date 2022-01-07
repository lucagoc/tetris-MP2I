#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


const int NBLINES = 22;
const int NBCOLUMNS = 10;

const bool DEBUG_MODE = false;


/*Vérifie si le joueur n'a pas perdu, c'est-à-dire si aucun bloc ne touche la ligne au dessus de la grille une fois placé.*/
void isEndgame(int mainGrid[NBLINES][NBCOLUMNS],bool* inGame){
    for(int i = 0; i < NBCOLUMNS ; i++){
        if(mainGrid[1][i] != 0){
            *inGame = false;
        }
    }
}

/* Définit le délai de descente en fonction de la difficulté. */
int setDifficulty(char* difficulty){
    int time_cycle;
    switch(*difficulty){
        case 't':
            time_cycle=900;
            break;
        case 'f':
            time_cycle=600;
            break;
        case 'n':
            time_cycle=300;
            break;
        case 'd':
            time_cycle=150;
            break;

    };
    return time_cycle;
}

/* Définit le délai de placement en fonction de la difficulté. */
int setDelay(char* difficulty){
    int delay;
    switch(*difficulty){
        case 't':
            delay=700;
            break;
        case 'f':
            delay=500;
            break;
        case 'n':
            delay=300;
            break;
        case 'd':
            delay=100;
            break;

    };
    return delay;
}

/* Renvoie le nombre de points à chaque ligne remplie en fct.*/
int setPointsperLine(char* difficulty){
    int points_per_line;
    switch(*difficulty){
        case 't':
            points_per_line=4 ;
            break;
        case 'f':
            points_per_line=10;
            break;
        case 'n':
            points_per_line=40;
            break;
        case 'd':
            points_per_line=100;
            break;

    };
    return points_per_line;
}
