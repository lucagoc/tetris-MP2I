#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include "regles.h"


void affiche_debug(int movingrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
	if(debug){
		for (int i = 0; i < nblignes; ++i)
	    {
	    	for (int j = 0; j < nbcolonnes; ++j)
	        {
	            move(i,30+j);
	            printw("%d", grille[i][j]);
	            move(i,60+j);
	            printw("%d", movingrid[i][j]);
	        }
	    }
	}
	refresh();
}

void debug_head(FILE* fp){
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void debug_start(FILE* fp){
	debug_head(fp);
	fprintf(fp, "Programme démarré");
}