#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "functions.h"
#include <stdlib.h>


/* extern int* generation_bloc(int id,int x,int y,int id_couleur);
extern void* affichage_tab(int tab[],int longueur);  */

int main(){

    int* bloc=malloc(5*sizeof(int));
    generation_bloc(bloc,2,3,4,1);
    for(int i=0;i<=4;i++){
        printf("[%d]",bloc[i]);
    }
    int grille[20][25];
    grille_vide(grille);
    grille[1][1]=1;
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    raw();
    
    //move(10,10);
    //printw("test");
    WINDOW *fenetre = newwin(20,25,0,0);
    refresh();
    box(fenetre,0,0);
    wrefresh(fenetre);
    for(int x=0;x<=19;x++){
        for (int y; y<=24;y++){
            wmove(fenetre,x,y);
            wprintw(fenetre,"%d",grille[x][y]);
        }
    }

    wrefresh(fenetre);
    getch();

    endwin(); 



    free(bloc);

    return 0;

}
   