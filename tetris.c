#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include "interface.h"
#include "regles.h"


int main(){

    int tetrimino_test[5][2];
    int tetrimino_test_2[5][2];

    int grille[nblignes][nbcolonnes];
    grille_vide(grille);

    WINDOW *fenetre = newwin(nblignes,nbcolonnes,0,0); //création de la fenêtre de jeu
    initialisation_interface(grille, fenetre);

    generation_tetrimino(tetrimino_test,2,3,4,1);
    generation_tetrimino(tetrimino_test_2,3,5,6,1);
    
    tetrimino_dans_grille(tetrimino_test,grille);
    tetrimino_dans_grille(tetrimino_test_2,grille);


    /*Commande de controle*/
    int key;
    while(((key) = getch()) != 'q'){ //Touche Q pour quitter la boucle.

        timeout(1000);// définie une seconde d'attente pour le getch, retourne ERR si rien n'est pressé.

        if(key = KEY_LEFT){
            //fonction de déplacement vers la gauche
        }
        if(key = KEY_RIGHT){
            //fonction de déplacement vers la droite
        }
        if(key = KEY_DOWN){
            //fonction de déplacement vers le bas
        }
        if(key = KEY_UP){
            //fonction de déplacement vers le bas d'un seul coup
        }

        wrefresh(fenetre);

        delai(1); //délai de 1 seconde.
    }

    endwin();


    return 0;

}
   
