#include <ncurses.h>
#include <stdio.h>
#include <time.h>

#include "regles.h"
#include "functions.h"

/*Bloc de DEBUG, a un affichage particulier pour être différencié des blocs classiques.*/
const int BLOCK_DEBUG = -1;

/*Affiche les valeurs internes au matrice utilisé par le jeu*/
void drawDebug(int mobileGrid[NBLINES][NBCOLUMNS], int mainGrid[NBLINES][NBCOLUMNS]){
	if(DEBUG_MODE){
		for (int i = 0; i < NBLINES; i++)
	    {
	    	for (int j = 0; j < NBCOLUMNS; j++)
	        {
	            move(i,30+j);
	            printw("%d", mainGrid[i][j]);
	            move(i,60+j);
	            printw("%d", mobileGrid[i][j]);
	            move(0,90+j);
	            printw("%d", j);
	        }
	        move(i,90);
	        printw("%d", i);
	    }
		refresh();
	}
}

/*Ecrit la date au début de chaque ligne du logfile*/
void printLogdate(FILE* fp){
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	fprintf(fp, "\n[%d-%02d-%02d %02d:%02d:%02d] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/*Génère un bloc avec 9 valeurs différentes. La fonction n'effectue pas de vérification*/
void genDebugtetrimino(int mobileGrid[NBLINES][NBCOLUMNS]){
	if(DEBUG_MODE){
		initGrid(mobileGrid);
		mobileGrid[0][0]=BLOCK_DEBUG;
        mobileGrid[0][1]=BLOCK_VIDE;
        mobileGrid[0][2]=BLOCK_O;
        mobileGrid[1][0]=BLOCK_I;
        mobileGrid[1][1]=BLOCK_S;
        mobileGrid[1][2]=BLOCK_Z;
        mobileGrid[2][0]=BLOCK_L;
        mobileGrid[2][1]=BLOCK_J;
        mobileGrid[2][2]=BLOCK_T;
	}
}

/*Initialise le logfile*/
FILE* initLogfile(){
	if(DEBUG_MODE){
		FILE *fp;
        fp  = fopen("./logfile.log", "w");
        printLogdate(fp);
		fprintf(fp, "Programme démarré");
        return fp;
	}
}

/*Ecrit les touches pressés par le joueur dans le logfile*/
void printLogkey(FILE* fp, char dir){
	if(DEBUG_MODE){
		printLogdate(fp);
		fprintf(fp, "Touche %c pressée", dir);
	}
}
