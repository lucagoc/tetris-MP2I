#include <ncurses.h>

#include "regles.h"
#include "debug.h"
#include "functions.h"


/*Permet d'afficher la grille de jeu*/
void affiche_grille(int grille[nblignes][nbcolonnes], WINDOW *fenetre){
    box(fenetre, 0, 0);
    wrefresh(fenetre);
    for(int x = 0; x < nblignes; x++){
        for (int y = 0; y < nbcolonnes; y++){
            wmove(fenetre,x+1,y+1);

            /*Implémentation des couleurs selon le type du bloc*/
            if(grille[x][y] == bloc_O){
                wattron(fenetre, COLOR_PAIR(bloc_O));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_O));
            } else if(grille[x][y] == bloc_I){
                wattron(fenetre, COLOR_PAIR(bloc_I));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_I));
            } else if(grille[x][y] == bloc_S){
                wattron(fenetre, COLOR_PAIR(bloc_S));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_S));
            } else if(grille[x][y] == bloc_Z){
                wattron(fenetre, COLOR_PAIR(bloc_Z));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_Z));
            } else if(grille[x][y] == bloc_L){
                wattron(fenetre, COLOR_PAIR(bloc_L));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_L));
            } else if(grille[x][y] == bloc_J){
                wattron(fenetre, COLOR_PAIR(bloc_J));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_J));
            } else if(grille[x][y] == bloc_T){
                wattron(fenetre, COLOR_PAIR(bloc_T));
                wprintw(fenetre," ");
                wattroff(fenetre, COLOR_PAIR(bloc_T));
            }
        }
    }
    if (debug){
        affiche_debug(grille);
    }
    wrefresh(fenetre);
    refresh();
}

/*Fonction qui définie les propriétés de l'affichage lors de son démarrage*/
void initialisation_interface(){
	
	initscr();  // Initialise l'affichage
    start_color();  // Initialise la palette de couleur

    // Définition des couleurs
    init_pair(bloc_O, COLOR_WHITE, COLOR_YELLOW);
    init_pair(bloc_I, COLOR_WHITE, COLOR_CYAN);
    init_pair(bloc_S, COLOR_WHITE, COLOR_GREEN);
    init_pair(bloc_Z, COLOR_WHITE, COLOR_RED);
    init_pair(bloc_L, COLOR_WHITE, COLOR_WHITE);
    init_pair(bloc_J, COLOR_WHITE, COLOR_BLUE);
    init_pair(bloc_T, COLOR_WHITE, COLOR_MAGENTA);

    curs_set(0);  // Cache le curseur
    noecho();  // Cache les touches pressées
    refresh();
}