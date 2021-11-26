#include <ncurses.h>
#include "regles.h"


/*On définit ici des constantes pour attribuer les couleurs (sera utile lors de l'affichage avec ncurses)*/
const int rouge = 0;
const int orange = 1;
const int jaune = 2;
const int vert = 3;
const int bleu = 4;
const int violet = 5;

/*Permet d'afficher la grille de jeu*/
void affiche_grille(int grille[nblignes][nbcolonnes], WINDOW *fenetre){
    box(fenetre,0,0);
    wrefresh(fenetre);
    for(int x=1;x<=18;x++){
        for (int y=1; y<=23;y++){
            if (grille[x][y]!=0){
                wmove(fenetre,x,y);
                wprintw(fenetre,"X");
            }
        }
    }
    wrefresh(fenetre);
}

/*Fonction qui définie les propriétés de l'affichage lors de son démarrage*/
void initialisation_interface(){
	
	initscr();  // Initialise l'affichage
    start_color();  // Initialise la palette de couleur
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Définition des couleurs
    curs_set(0);  // Cache le curseur
    noecho();  // Cache les touches pressées
    refresh();
}