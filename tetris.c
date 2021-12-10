#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include "interface.h"
#include "regles.h"
#include "debug.h"


int main(){

    /*Ecrit un fichier de debug si le debug mode est activé voir regles.c*/
    if(debug){
        FILE *fp;
        fp  = fopen("./logfile.log", "w");
        debug_start(fp);
    }

    int grille[nblignes][nbcolonnes];
    int movinggrid[nblignes][nbcolonnes];

    init_grille(grille);

    initialisation_interface();
    WINDOW *fenetre = newwin(nblignes+2,nbcolonnes+2,0,0); //création de la fenêtre de jeu

    generation_tetrimino(movinggrid, 3);
    grille[3][9] = 2;
    grille[4][9] = 2;
    grille[5][9] = 2;
    grille[6][9] = 2;

    grille[3][5] = 6;
    grille[4][5] = 6;
    grille[5][5] = 6;
    grille[5][4] = 6;

    draw_interface(grille, movinggrid, fenetre);

    /*Commande de controle*/
    int key;
    bool ingame = true;
    while(ingame == true){ 
        key = wgetch(fenetre);

        /*timeout(1000);*/ //défini une seconde d'attente pour le getch, retourne ERR si rien n'est pressé.

        switch(key){
            case 66: //Touche flèche bas
                deplacement_bas(movinggrid, grille);
                break;
            case 67: //Touche flèche droite
                //translation(movinggrid, grille, r);
                break;
            case 68: //Touche flèche gauche
                //translation(movinggrid, grille, l);
                break;
            case 'q': //Touche Q pour quitter la boucle.
                ingame = false;
                endwin();
                exit(0);
        };

        draw_interface(grille, movinggrid, fenetre);
    }

    endwin();

    return 0;

}
   
