#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include "interface.h"
#include "regles.h"
#include "debug.h"


int main(){

    /*Ecrit un fichier de debug si le debug mode est activé, voir regles.c*/

    FILE *fp = debug_start();

    int grille[nblignes][nbcolonnes];
    int movinggrid[nblignes][nbcolonnes];

    init_grille(grille);

    initialisation_interface();
    WINDOW *fenetre = newwin(nblignes+2,nbcolonnes+2,0,0); //création de la fenêtre de jeu

    generation_tetrimino(movinggrid, 3);

    grille[16][9] = 2;
    grille[17][9] = 2;
    grille[18][9] = 2;
    grille[19][9] = 2;

    grille[8][5] = 6;
    grille[9][5] = 6;
    grille[10][5] = 6;
    grille[10][4] = 6;

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
                debug_write_deplacement(fp, 'D');
                break;
            case 67: //Touche flèche droite
                deplacement_droite(movinggrid, grille);
                debug_write_deplacement(fp, 'R');
                break;
            case 68: //Touche flèche gauche
                deplacement_gauche(movinggrid, grille);
                debug_write_deplacement(fp, 'L');
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
   
