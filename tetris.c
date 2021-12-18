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
    init_grille(movinggrid);

    initialisation_interface();
    WINDOW *fenetre = newwin(nblignes,(nbcolonnes*2)+2,0,0); //création de la fenêtre de jeu, nombre de colonnes multiplié par 2 pour faire des carrés.
    draw_interface(grille, movinggrid, fenetre);

    generation_tetrimino(movinggrid);

    /*Commande de controle*/
    int key;
    bool ingame = true;
    while(ingame == true){

        key = wgetch(fenetre);
        
        switch(key){
            case 65:
                teleportation_bas(movinggrid, grille);
                debug_write_keypress(fp, '^');
                break;
            case 66: //Touche flèche bas
                deplacement_bas(movinggrid, grille);
                debug_write_keypress(fp, 'B');
                break;
            case 67: //Touche flèche droite
                deplacement_droite(movinggrid, grille);
                debug_write_keypress(fp, '>');
                break;
            case 68: //Touche flèche gauche
                deplacement_gauche(movinggrid, grille);
                debug_write_keypress(fp, '<');
                break;
            case 'q': //Touche Q pour quitter la boucle.
                ingame = false;
                endwin();
                exit(0);
            case 'd': //Rotation
                rotation_horaire(movinggrid,grille);
                debug_write_keypress(fp, 'd');
                break;
            case 'y': //Génére un bloc de debug
                debug_tetrimino(movinggrid);
                debug_write_keypress(fp, 'y');
                break;
        };
        draw_interface(grille, movinggrid, fenetre);
        
    }


    endwin();
    return 0;

}
