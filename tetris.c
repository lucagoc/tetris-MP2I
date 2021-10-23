#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "functions.h"
#include <stdlib.h>


/* extern int* generation_bloc(int id,int x,int y,int id_couleur);
extern void* affichage_tab(int tab[],int longueur);  */

int main(){

    int* bloc=malloc(5*sizeof(int));
    
    printf(generation_bloc(bloc[],2,0,0,4);

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);


    
    refresh();
    getch();

    endwin(); 

    /*cbreak();*/ 

    free(bloc);

    return 0;

}
   