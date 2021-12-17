#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


const int nblignes = 22 ;
const int nbcolonnes = 10;

const bool debug = true;


/*Cette fonction permet de vérifier si le joueur n'a pas perdu, c'est-à-dire si aucun bloc ne touche la ligne au dessus de la grille une fois placé.*/
void endgame(int grille[nblignes][nbcolonnes]){
    for(int i = 0; i < nbcolonnes ; i++){
        if(grille[1][i] != 0){
            endwin();
            printf("Fin de partie\n");
            exit(0);
            //ceci n'est qu'une solution temporaire de fin de partie, on fera mieux une fois que l'on aura les rotations et le temps OK 
        }
    }
}
