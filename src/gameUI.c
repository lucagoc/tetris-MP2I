#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

#include "header/rules.h"
#include "header/tetrimino.h"
#include "header/debug.h"


/* Mets le jeu en pause en cachant l'affichage */
void pause(time_t* timeStarted){
    
    time_t timePausestart = time(NULL);

    /* Affichage fenêtre*/
    WINDOW *pauseWindow = newwin(NBLINES,(NBCOLUMNS*2)+2, 1, 3);
    box(pauseWindow, 0, 0);

    /* Message pause */
    wmove(pauseWindow, NBLINES/2, NBCOLUMNS-3);
    wprintw(pauseWindow, "En pause");
    wrefresh(pauseWindow);

    timeout(-1);
    getch();

    time_t timePauseend = time(NULL);
    *timeStarted += (timePauseend-timePausestart);
    
    return;
}

/* Bloque l'exécution pendant une durée entrée en milliseconde */
void delay(int ms)
{
    clock_t time = clock();
    while (clock() < time + ms);
}

/* Affiche la grille de jeu dans l'interface ncurses */
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

    return;
}

/* Affiche la prévisualisation de l'emplacement des tetrimino. Voir documentation pour plus de détails */
void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow){

    /* Copie de la mobileGrid */
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

/* Affiche le contenu de l'inventaire. */
void drawInventory(int tetriminoID, WINDOW *inventoryWindow){

    /*Implémentation des couleurs selon le type du bloc*/
    if(tetriminoID == BLOCK_O){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_O));
        wmove(inventoryWindow, 2, 2*2);
        wprintw(inventoryWindow, "    ");
        wmove(inventoryWindow, 3, 2*2);
        wprintw(inventoryWindow, "    ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_O));
    } else if(tetriminoID == BLOCK_I){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_I));
        wmove(inventoryWindow, 2, 1*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 2, 2*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 2, 3*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 2, 4*2);
        wprintw(inventoryWindow, "  ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_I));
    } else if(tetriminoID == BLOCK_S){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_S));
        wmove(inventoryWindow, 2, 3*2);
        wprintw(inventoryWindow, "    ");
        wmove(inventoryWindow, 3, 2*2);
        wprintw(inventoryWindow, "    ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_S));
    } else if(tetriminoID == BLOCK_Z){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_Z));
        wmove(inventoryWindow, 2, 2*2);
        wprintw(inventoryWindow, "    ");
        wmove(inventoryWindow, 3, 3*2);
        wprintw(inventoryWindow, "    ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_Z));
    } else if(tetriminoID == BLOCK_L){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_L));
        wmove(inventoryWindow, 2, 3*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 3, 1*2);
        wprintw(inventoryWindow, "      ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_L));
    } else if(tetriminoID == BLOCK_J){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_J));
        wmove(inventoryWindow, 2, 1*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 3, 1*2);
        wprintw(inventoryWindow, "      ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_J));
    } else if(tetriminoID == BLOCK_T){
        wattron(inventoryWindow, COLOR_PAIR(BLOCK_T));
        wmove(inventoryWindow, 2, 2*2);
        wprintw(inventoryWindow, "  ");
        wmove(inventoryWindow, 3, 1*2);
        wprintw(inventoryWindow, "      ");
        wattroff(inventoryWindow, COLOR_PAIR(BLOCK_T));
    } else if(tetriminoID == BLOCK_DEBUG){
        wmove(inventoryWindow, 2, 2*2);
        wprintw(inventoryWindow, "{}");
    }
}

/* Affichage du mode de jeu */
void drawGameMode(int gameMode){
    move(NBLINES+3, 4);
    if (gameMode == 0){
        printw("Mode de jeu : Temps");
    }else{
        printw("Mode de jeu : Points");
    }
    return;
}

/* Affichage du score */
void drawScore(int score){
    move(NBLINES+5, 4);
    printw("Score : %d", score);
    return;
}

/* Affichage du temps écoulé */
void drawTimer(int timer){
    move(NBLINES+7, 4);
    printw("Temps écoulé : %d", timer);
    return;
}

/* Affichage de la difficulté choisi */
void drawDifficulty(int difficulty){

    move(NBLINES+1, 4);
    if (difficulty == 0) printw("Difficulté : Très Facile");
    else if (difficulty == 1) printw("Difficulté : Facile");
    else if (difficulty == 2) printw("Difficulté : Normal");
    else if (difficulty == 3) printw("Difficulté : Difficile");
    else printw("Difficulté : INCONNUE");
    
    return;
}

/*Affiche les touches pour jouer à gauche*/
void drawCommands(){

    move(2,NBCOLUMNS+17);
    printw("Descente instantanée : Flèche du haut");
    move(4,NBCOLUMNS+17);
    printw("Gauche : Flèche de gauche");
    move(6,NBCOLUMNS+17);
    printw("Droite : Flèche du droite");
    move(8,NBCOLUMNS+17);
    printw("Bas : Flèche du bas");
    move(10,NBCOLUMNS+17);
    printw("Rotation : D");
    move(12,NBCOLUMNS+17);
    printw("Pause : P");
    move(14,NBCOLUMNS+17);
    printw("Quitter le jeu : Q");
    move(16,NBCOLUMNS+17);
    printw("Touche Réserve : S");
    move(18,NBCOLUMNS+17);
    printw("Réserve :");

    return;
}

/* Affiche l'interface du jeu. */
void drawGame(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, int score, int timer, int difficulty, WINDOW *gridWindow, int gameMode){

    werase(gridWindow);

    /* Affichage de la grille */
    box(gridWindow, 0, 0);
    drawGrid(mainGrid, gridWindow);
    drawGhostblocks(mainGrid, mobileGrid, gridWindow);
    drawGrid(mobileGrid, gridWindow);

    /* Affichage du tetrino dans l'inventaire dans une fenêtre temporaire */
    WINDOW *inventoryWindow = newwin(6, 12, 18, (NBCOLUMNS*2)+17);
    box(inventoryWindow, 0, 0);
    drawInventory(inventory, inventoryWindow);

    /* Affichage annexe */
    drawScore(score);
    drawGameMode(gameMode);
    drawTimer(timer);
    drawDifficulty(difficulty);
    drawCommands();
    drawDebug(mobileGrid, mainGrid);

    wrefresh(gridWindow);
    wrefresh(inventoryWindow);
    refresh();

    delwin(inventoryWindow);  // Pour ne pas surcharger la mémoire.
}


/* Affiche un clignotement sur une ligne donnée */
void blinkLine(int line){
    for(int n = 0; n < 5; n++){

        /* Affiche une couleur blanche sur la ligne donné */
        attron(COLOR_PAIR(BLOCK_L));
        for (int j = 0; j < NBCOLUMNS; j++){
            move(line, (j*2)+4);
            printw("  ");
        }
        refresh();
        attroff(COLOR_PAIR(BLOCK_L));

        delay(40000);   // Délai avant la prochaine frame

        /* Affiche une couleur noir sur la ligne donné*/
        attron(COLOR_PAIR(BLOCK_VIDE));
        for (int j = 0; j < NBCOLUMNS; j++){
            move(line, (j*2)+4);
            printw("  ");
        }
        refresh();
        attroff(COLOR_PAIR(BLOCK_VIDE));

        delay(40000);   // Délai avant la prochaine frame
    }

    return;
}