#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "functions.h"
#include <stdlib.h>


int main(){

    int ligne = 20;
    int colonne = 25;
    int tetrimino_test[5][2];
    int tetrimino_test_2[5][2];

    generation_tetrimino(tetrimino_test,2,3,4,1);
    generation_tetrimino(tetrimino_test_2,3,5,6,1);

    
    int grille[ligne][colonne];
    grille_vide(grille);
    
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    raw();
    WINDOW *fenetre = newwin(20,25,0,0);
    refresh();
    box(fenetre,0,0);
    wrefresh(fenetre);
    tetrimino_dans_grille(tetrimino_test,grille);
    tetrimino_dans_grille(tetrimino_test_2,grille);
    affiche_grille(grille,fenetre);
    wrefresh(fenetre);
    

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
   
