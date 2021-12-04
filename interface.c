#include <ncurses.h>
#include "regles.h"
#include "debug.h"


/*On définit ici des constantes pour attribuer les couleurs (sera utile lors de l'affichage avec ncurses)*/
const int rouge = 0;
const int orange = 1;
const int jaune = 2;
const int vert = 3;
const int bleu = 4;
const int violet = 5;

/*Permet d'afficher la grille de jeu*/
void affiche_grille(int grille[nblignes][nbcolonnes], WINDOW *fenetre){
    wbkgd(fenetre, COLOR_PAIR(1));
    box(fenetre, 0, 0);
    wrefresh(fenetre);
    for(int x = 0; x < nblignes; x++){
        for (int y = 0; y < nbcolonnes; y++){
            if (grille[x][y] != 0){
                wattron(fenetre, COLOR_PAIR(2));
                wmove(fenetre,x+1,y+1);
                wprintw(fenetre," "); //Affichage d'un espace avec une palette de couleur différente pour faire un rectangle
                wattroff(fenetre, COLOR_PAIR (2));
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
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));  // Définition des couleurs
    curs_set(0);  // Cache le curseur
    noecho();  // Cache les touches pressées
    refresh();
}