#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


const int nblignes = 20;
const int nbcolonnes = 25;


/*Cette fonction permet de vérifier si le joueur n'a pas perdu, c'est-à-dire si aucun bloc ne touche le haut de l'écran*/
bool endgame(int* grille){
    for(int i=0;i<10;i++){ /*Ici, on fait bouger i de 0 à 9 pour étudier toutes les positions du haut de l'écran*/
        if(i!=0){
            return true; /*Si l'une des positions est prise, alors le joueur a perdu, on renvoie alors true pour indiquer que le jeu est fini*/
        }
    }
    return false; /*Si l'exécution se poursuit jusqu'à ce stade, cela signifie alors que aucune position n'est prise, on indique alors que tout va bien*/
}
