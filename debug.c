#include <ncurses.h>
#include <stdio.h>
#include <time.h>

#include "regles.h"
#include "functions.h"

/*Bloc de DEBUG, a un affichage particulier pour être différencié des blocs classiques.*/
const int bloc_DEBUG = -1;

/*Affiche les valeurs internes au matrice utilisé par le jeu*/
void affiche_debug(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
	if(debug){
		for (int i = 0; i < nblignes; i++)
	    {
	    	for (int j = 0; j < nbcolonnes; j++)
	        {
	            move(i,30+j);
	            printw("%d", grille[i][j]);
	            move(i,60+j);
	            printw("%d", movinggrid[i][j]);
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
void debug_head(FILE* fp){
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	fprintf(fp, "\n[%d-%02d-%02d %02d:%02d:%02d] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/*Génère un bloc avec 9 valeurs différentes. La fonction n'effectue pas de vérification*/
void debug_tetrimino(int movinggrid[nblignes][nbcolonnes]){
	if(debug){
		init_grille(movinggrid);
		movinggrid[0][0]=bloc_DEBUG;
        movinggrid[0][1]=bloc_VIDE;
        movinggrid[0][2]=bloc_O;
        movinggrid[1][0]=bloc_I;
        movinggrid[1][1]=bloc_S;
        movinggrid[1][2]=bloc_Z;
        movinggrid[2][0]=bloc_L;
        movinggrid[2][1]=bloc_J;
        movinggrid[2][2]=bloc_T;
	}
}

/*Initialise le logfile*/
FILE* debug_start(){
	if(debug){
		FILE *fp;
        fp  = fopen("./logfile.log", "w");
        debug_head(fp);
		fprintf(fp, "Programme démarré");
        return fp;
	}
}

/*Ecrit les touches pressés par le joueur dans le logfile*/
void debug_write_keypress(FILE* fp, char dir){
	if(debug){
		debug_head(fp);
		fprintf(fp, "Touche %c pressée", dir);
	}
}

