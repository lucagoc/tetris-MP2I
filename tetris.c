#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "functions.h"
#include <stdlib.h>


/* extern int* generation_tetrimino(int id,int x,int y,int id_couleur);
extern void* affichage_tab(int tab[],int longueur);  */

int main(){
    /* tests */
    int* tetrimino_test=malloc(10*sizeof(int));
    generation_tetrimino(tetrimino_test,2,3,4,1);
    for(int i=0;i<=4;i++){
        printf("[%d]",tetrimino_test[i]);
    }
    /* tests */
    
    int grille[20][25];
    grille_vide(grille);
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    raw();
    
    WINDOW *fenetre = newwin(20,25,0,0);
    refresh();
    box(fenetre,0,0);
    wrefresh(fenetre);
    tetrimino_dans_grille(tetrimino_test,grille);
    affiche_grille(grille,fenetre);

    wrefresh(fenetre);
    getch();

    endwin(); 

    free(tetrimino_test);

    return 0;

}
   