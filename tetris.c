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
    int inventaire = 0; //inventaire vide
    bool inv_used = false; // Permet de savoir si l'inventaire a été utilisé.

    init_grille(grille);
    init_grille(movinggrid);

    initialisation_interface();
    WINDOW *fenetre = newwin(nblignes,(nbcolonnes*2)+2,0,0); //création de la fenêtre de jeu, nombre de colonnes multiplié par 2 pour faire des carrés.
    draw_interface(grille, movinggrid, inventaire, fenetre);

    int id_bloc = generation_tetrimino(movinggrid, genRandom(0));
    int id_blocA = id_bloc; //Utile pour les comparaisons.

    /*Commande de controle*/
    int key;
    bool ingame = true;
    while(ingame == true){

        key = wgetch(fenetre);

        //Réactive l'accès à l'inventaire si le bloc a changé
        if(id_bloc != id_blocA) inv_used = false;
        
        switch(key){
            case 65: //flèche haut
                teleportation_bas(movinggrid, grille);
                id_bloc = placer(movinggrid, grille, id_bloc);
                debug_write_keypress(fp, '^');
                break;
            case 66: //Touche flèche bas
                id_bloc = deplacement_bas(movinggrid, grille, id_bloc);
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
                rotation(movinggrid,grille);
                debug_write_keypress(fp, 'd');
                break;
            case 'y': //Génére un bloc de debug
                debug_tetrimino(movinggrid);
                debug_write_keypress(fp, 'y');
                id_bloc = bloc_DEBUG;
                break;
            case 's': //Réserve
                if(inv_used == false){
                    if(inventaire == 0){ // Cas où il n'y a pas encore de bloc dans l'inventaire.
                        init_grille(movinggrid);
                        inventaire = id_bloc;
                        id_bloc = generation_tetrimino(movinggrid, genRandom(id_bloc));
                        id_blocA = id_bloc;
                    } else { // Cas normal
                        int temp = id_bloc;
                        init_grille(movinggrid);
                        id_bloc = generation_tetrimino(movinggrid, inventaire);
                        id_blocA = id_bloc;
                        inventaire = temp;
                    }
                    inv_used = true;
                }
                debug_write_keypress(fp, 's');
                break;
            case 'p': //Pause
                pause();
                debug_write_keypress(fp, 'p');
                break;
        };

        draw_interface(grille, movinggrid, inventaire, fenetre);
    }

    endwin();
    return 0;
}
