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

    int tetrimino_test[5][2];
    int tetrimino_test_2[5][2];

    int grille[nblignes][nbcolonnes];
    grille_vide(grille);

    initialisation_interface();
    WINDOW *fenetre = newwin(nblignes+2,nbcolonnes+2,0,0); //création de la fenêtre de jeu

    generation_tetrimino(tetrimino_test,2,3,4,1);
    generation_tetrimino(tetrimino_test_2,3,5,6,1);

    translation(tetrimino_test,'r',grille);
    translation(tetrimino_test,'r',grille);
    translation(tetrimino_test,'r',grille);
    tetrimino_dans_grille(tetrimino_test,grille);
    tetrimino_dans_grille(tetrimino_test_2,grille);
    
    affiche_grille(grille,fenetre);

    /*Commande de controle*/
    int key;
    bool ingame = true;
    while(ingame == true){ 
        key = wgetch(fenetre);

        /*timeout(1000);*/ //défini une seconde d'attente pour le getch, retourne ERR si rien n'est pressé.

        switch(key){
            case 66: //Touche flèche bas
                deplacement_bas(tetrimino_test,grille);
                tetrimino_dans_grille(tetrimino_test,grille);
                break;
            case 67: //Touche flèche droite
                translation(tetrimino_test,'r',grille);
                tetrimino_dans_grille(tetrimino_test,grille);
                break;
            case 68: //Touche flèche gauche
                translation(tetrimino_test,'l',grille);
                tetrimino_dans_grille(tetrimino_test,grille);
                break;
            case 'q': //Touche Q pour quitter la boucle.
                ingame = false;
                endwin();
                exit(0);
        };

        wclear(fenetre);
        affiche_grille(grille,fenetre);
    }

    endwin();

    return 0;

}
   
