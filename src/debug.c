#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "header/rules.h"
#include "header/tetrimino.h"

/*	Ce fichier sert uniquement à l'exécution du module "debug",
 *	qui sert essentiellement à garder une trace au fil du temps
 *  d'une partie de tetris.
 */

const bool DEBUG_MODE = false;

/*Bloc à l'affichage particulier pour être différencié des blocs classiques.*/
const int BLOCK_DEBUG = -1;

/*Affiche les valeurs des matrices utilisées par le jeu*/
void drawDebug(int mobileGrid[NBLINES][NBCOLUMNS], int mainGrid[NBLINES][NBCOLUMNS]){
	if(DEBUG_MODE){
		for (int i = 0; i < NBLINES; i++)
	    {
	    	for (int j = 0; j < NBCOLUMNS; j++)
	        {
	            move(i,70+j);
	            printw("%d", mainGrid[i][j]);
	            move(i,100+j);
	            printw("%d", mobileGrid[i][j]);
	            move(0,130+j);
	            printw("%d", j);
	        }
	        move(i,130);
	        printw("%d", i);
	    }
		refresh();
	}
}

/*Génère un bloc avec 9 valeurs différentes.*/
void genDebugtetrimino(int mobileGrid[NBLINES][NBCOLUMNS]){
	if(DEBUG_MODE){
		initGrid(mobileGrid);
		mobileGrid[0][0] = BLOCK_DEBUG;
        mobileGrid[0][1] = BLOCK_VIDE;
        mobileGrid[0][2] = BLOCK_O;
        mobileGrid[1][0] = BLOCK_I;
        mobileGrid[1][1] = BLOCK_S;
        mobileGrid[1][2] = BLOCK_Z;
        mobileGrid[2][0] = BLOCK_L;
        mobileGrid[2][1] = BLOCK_J;
        mobileGrid[2][2] = BLOCK_T;
	}
}
