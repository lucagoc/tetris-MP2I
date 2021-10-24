#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "functions.h"
#include <stdlib.h>


/* extern int* generation_bloc(int id,int x,int y,int id_couleur);
extern void* affichage_tab(int tab[],int longueur);  */


int main(){

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    /*Grille du jeu de tetris 12x22*/
    int grille[12][22];

    /*fonction qui génère le bloc selon son ID, indiqué dans le header*/
    int bloc = J;// <-- ID du bloc vas-y change-le tu veras c'est fou.
    int* t = generation_bloc(bloc);
    
    /*Récupérer la taille de grille du tetromino pour l'affichage, pas optimiser du tout mais c'est temporaire*/
    int n;
    if (bloc == I){
        n = 5;
    } else {
        n = 3;
    }

    /*Affichage du bloc créé*/
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n; ++k)
        {
             printw("%d", t[n*i+k]);
        }
        printw("\n");
        
    }

    refresh();
    getch();
    endwin();
    free(t);

    return 0;

}
