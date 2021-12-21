#include <ncurses.h>

#include "regles.h"
#include "debug.h"
#include "functions.h"


/*Permet d'afficher la grille de jeu*/
void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow){
    for(int x = 2; x < NBLINES; x++){
        for (int y = 0; y < NBCOLUMNS; y++){
            wmove(gridWindow,x-1,(y*2)+1);

            /*Implémentation des couleurs selon le type du bloc*/

            if(grid[x][y] == BLOCK_O){
                wattron(gridWindow, COLOR_PAIR(BLOCK_O));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_O));
            } else if(grid[x][y] == BLOCK_I){
                wattron(gridWindow, COLOR_PAIR(BLOCK_I));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_I));
            } else if(grid[x][y] == BLOCK_S){
                wattron(gridWindow, COLOR_PAIR(BLOCK_S));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_S));
            } else if(grid[x][y] == BLOCK_Z){
                wattron(gridWindow, COLOR_PAIR(BLOCK_Z));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_Z));
            } else if(grid[x][y] == BLOCK_L){
                wattron(gridWindow, COLOR_PAIR(BLOCK_L));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_L));
            } else if(grid[x][y] == BLOCK_J){
                wattron(gridWindow, COLOR_PAIR(BLOCK_J));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_J));
            } else if(grid[x][y] == BLOCK_T){
                wattron(gridWindow, COLOR_PAIR(BLOCK_T));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_T));
            } else if(grid[x][y] == BLOCK_DEBUG){
                wprintw(gridWindow,"{}");
            }
        }
    }
}

/*permet de prévisualiser l'emplacement du tetrimino*/
void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow){

    /*Copie de la mobileGrid*/
    int tempGrid[NBLINES][NBCOLUMNS];
    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++){
            tempGrid[i][j] = mobileGrid[i][j];
        }
    }

    goBottom(mainGrid, tempGrid);
    
    /*Affichage des ghostblocs*/
    for(int x = 2; x < NBLINES; x++){
        for (int y = 0; y < NBCOLUMNS; y++){
            if(tempGrid[x][y] != 0) {
                wmove(gridWindow,x-1,(y*2)+1);
                wprintw(gridWindow,"[]");
            }
        }
    }
    return;
}

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventaire, WINDOW *gridWindow){

    werase(gridWindow); //efface la frame précédente

    box(gridWindow, 0, 0);
    drawGrid(mainGrid, gridWindow);
    drawGhostblocks(mainGrid, mobileGrid, gridWindow);
    drawGrid(mobileGrid, gridWindow);

    /*Affichage de celui qui est stocké*/
    /*move(NBLINES+2,2);
    printw("%d", inventaire);*/

    if (DEBUG_MODE){
        drawDebug(mobileGrid, mainGrid);
    }

    wrefresh(gridWindow);
    refresh();
}

void draw_commands(){
    move(1,25);
    printw("Descente instantanée : Flèche du haut");
    move(3,25);
    printw("Gauche : Flèche de gauche");
    move(5,25);
    printw("Droite : Flèche du droite");
    move(7,25);
    printw("Bas : Flèche du bas");
    move(9,25);
    printw("Rotation : D");
    move(11,25);
    printw("Pause : P");
    move(13,25);
    printw("Quitter le jeu : Q");
    move(15,25);
    printw("Touche Réserve : S");
    move(17,25);
    printw("Réserve : ");
    refresh();
}

/*Fonction qui définie les propriétés de l'affichage lors de son démarrage*/
void initUI(){
	
	initscr();  // Initialise l'affichage
    start_color();  // Initialise la palette de couleur

    // Définition des couleurs
    init_pair(BLOCK_O, COLOR_WHITE, COLOR_YELLOW);
    init_pair(BLOCK_I, COLOR_WHITE, COLOR_CYAN);
    init_pair(BLOCK_S, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLOCK_Z, COLOR_WHITE, COLOR_RED);
    init_pair(BLOCK_L, COLOR_WHITE, COLOR_WHITE);
    init_pair(BLOCK_J, COLOR_WHITE, COLOR_BLUE);
    init_pair(BLOCK_T, COLOR_WHITE, COLOR_MAGENTA);

    draw_commands();

    curs_set(0);  // Cache le curseur
    noecho();  // Cache les touches pressées
    refresh();
}

void pause(){
    
    
    getch();
    
    
    return;
}

