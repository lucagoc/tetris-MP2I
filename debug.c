#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include "regles.h"


void affiche_debug(int movingrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
	if(debug){
		for (int i = 0; i < nblignes; i++)
	    {
	    	for (int j = 0; j < nbcolonnes; j++)
	        {
	            move(i,30+j);
	            printw("%d", grille[i][j]);
	            move(i,60+j);
	            printw("%d", movingrid[i][j]);
	            move(0,90+j);
	            printw("%d", j);
	        }
	        move(i,90);
	        printw("%d", i);
	    }
		refresh();
	}
}

void debug_head(FILE* fp){
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	fprintf(fp, "\n[%d-%02d-%02d %02d:%02d:%02d] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

FILE* debug_start(){
	if(debug){
		FILE *fp;
        fp  = fopen("./logfile.log", "w");
        debug_head(fp);
		fprintf(fp, "Programme démarré");
        return fp;
	}
}

void debug_write_deplacement(FILE* fp, char dir){
	if(debug){
		debug_head(fp);
		fprintf(fp, "Fonction de déplacement %c exécutée", dir);
	}
}
