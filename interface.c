#include <ncurses.h>
#include "regles.h"


/* on définit ici des constantes pour attribuer les couleurs (sera utile lors de l'affichage avec ncurses) */
const int rouge = 0;
const int orange = 1;
const int jaune = 2;
const int vert = 3;
const int bleu = 4;
const int violet = 5;


void affiche_grille(int grille[nblignes][nbcolonnes],WINDOW *fenetre){
    for(int x=1;x<=18;x++){
        for (int y=1; y<=23;y++){
            if (grille[x][y]!=0){
                wmove(fenetre,x,y);
                wprintw(fenetre,"X");
            }
        }
    }
}

void initialisation_interface(int grille[nblignes][nbcolonnes], WINDOW *fenetre){
	
	initscr(); //démarrage Ncurses

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); //définition des couleurs

    box(fenetre,0,0);
    
    affiche_grille(grille,fenetre); //initialisation de la grille

    refresh();
    wrefresh(fenetre);

}
