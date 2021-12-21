#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


const int NBLINES = 22;
const int NBCOLUMNS = 10;

const bool DEBUG_MODE = false;


/*Cette fonction permet de vérifier si le joueur n'a pas perdu, c'est-à-dire si aucun bloc ne touche la ligne au dessus de la grille une fois placé.*/
void isEndgame(int mainGrid[NBLINES][NBCOLUMNS]){
    for(int i = 0; i < NBCOLUMNS ; i++){
        if(mainGrid[1][i] != 0){
            endwin();
            printf("Fin de partie\n");
            exit(0);
            //ceci n'est qu'une solution temporaire de fin de partie, on fera mieux une fois que l'on aura les rotations et le temps OK 
        }
    }
}
