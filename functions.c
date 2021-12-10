#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "regles.h"

const int bloc_VIDE = 0;
const int bloc_O = 1; /* correspond au tétromino en forme de carré */
const int bloc_I = 2; /* correspond au tétromino en forme de bâton */
const int bloc_S = 3; /* correspond au tétromino en forme de biais inversé */
const int bloc_Z = 4; /* correspond au tétromino en forme de biais */
const int bloc_L = 5; /* correspond au tétromino en forme de L */
const int bloc_J = 6; /* correspond au tétromino en forme de L inversé */
const int bloc_T = 7; /* correspond au tétromino en forme de T */


/*Ce programme contient l'ensemble des fonctions à utiliser actuellement.*/


/*Cette fonction void permet de remplir de 0 la grille passée en entrées. Elle est plus rapide que si l'on remplaçait uniquement les 1 par des zéros, car il faudrait alors comparer*/
void init_grille(int grille[nblignes][nbcolonnes]){
    for (int x = 0; x < nblignes; x++){
        for (int y=0; y < nbcolonnes; y++){
            grille[x][y] = 0;
        }
    }
}

/*Cette fonction permet de placer un tetrimino directement prêt en haut de la grille secondaire*/
void generation_tetrimino(int movinggrid[nblignes][nbcolonnes],int id_bloc){
    init_grille(movinggrid); /*On nettoie notre grille en premier lieu*/

    /*les différents if correspondent à une disjonction de cas*/
    
    if(id_bloc == bloc_O){
        /* correspond au tétromino en forme de carré */
        movinggrid[0][5]=id_bloc;
        movinggrid[0][6]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[1][6]=id_bloc;
    } else if(id_bloc == bloc_I){
        /* correspond au tétromino en forme de baton */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[2][5]=id_bloc;
        movinggrid[3][5]=id_bloc;
    } else if (id_bloc == bloc_S){
        /* correspond au tétromino en forme de biais inversé */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[1][6]=id_bloc;
        movinggrid[2][6]=id_bloc;
    } else if (id_bloc == bloc_Z){
        /* correspond au tétromino en forme de biais */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[1][4]=id_bloc;
        movinggrid[2][4]=id_bloc;
    } else if (id_bloc == bloc_L){
        /* correspond au tétromino en forme de L */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[2][5]=id_bloc;
        movinggrid[2][6]=id_bloc;
    } else if (id_bloc == bloc_J){
        /* correspond au tétromino en forme de L inversé */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[2][5]=id_bloc;
        movinggrid[2][4]=id_bloc;
    } else if(id_bloc == bloc_T){
        /* correspond au tétromino en forme de T */
        movinggrid[0][5]=id_bloc;
        movinggrid[1][5]=id_bloc;
        movinggrid[1][4]=id_bloc;
        movinggrid[1][6]=id_bloc;
    }
}

/*Cette fonction permet de déplacer le bloc actuel dans la grille mouvante sans tenir compte des tests nécessaires avant*/
void deplacer(char dir, int movinggrid[nblignes][nbcolonnes]){
    for(int i = nblignes; i < 0; i++){ /*Cette boucle balaye toutes les lignes*/
        for(int j = nbcolonnes; j < 0; j++){ /*Et celle-ci toutes les colonnes. Pour éviter de descendre plusieurs fois un seul bloc, le scan de 'movinggrid' se fait du bas vers le haut*/
            if(movinggrid[i][j] != 0){ /*Si on repère un bloc non vide*/
                if(dir == 'd'){
                    movinggrid[i][j]=0;
                    movinggrid[i-1][j]=1;
                } else if(dir == 'l'){
                    movinggrid[i][j]=0;
                    movinggrid[i][j-1]=1;
                } else if(dir == 'r'){
                    movinggrid[i][j]=0;
                    movinggrid[i][j+1]=1;
                }
            }
        }
    }
}

void placer(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    for (int i = 0; i < nblignes; i++){
        for (int j = 0; j < nbcolonnes; j++){
            if(movinggrid[i][j] ==! 0){
                grille[i][j] = movinggrid[i][j];
            }
        }
    }
}

/*Cette fonction permet de descendre un bloc vers le bas lorsque c'est possible*/
void deplacement_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    for(int i=0; i > -nblignes ; i--){ /*Cette boucle balaye toutes les lignes*/
        for(int j = 0; j > -nbcolonnes; j--){ /*Et celle-ci toutes les colonnes*/
            if (movinggrid[i][j]!=0){
                if(grille[i-1][j]!=0){/*Si le carré dans 'grille' juste au-dessous de celui qu'on vient de détecter dans 'movinggrid' n'est pas vide, on ne peut pas descendre*/
                    placer(movinggrid,grille); /*Donc on place le bloc dans la grille*/
                } else if (i == -nblignes){
                    placer(movinggrid,grille); /*Et si on a atteint la ligne du bas, le bloc ne peut plus descendre, donc on le place dans 'grille'*/
                }
            }
        }
    }
    deplacer('d',movinggrid);/*Dans ce cas-là, on déplace le bloc vers le bas*/
}


void delai(int nb_secondes)
{
    clock_t temps = clock();
    while (clock() < temps + 1000*nb_secondes);
}

/*Ce qui reste à faire : L'étude du cas pour translation (il suffit de s'inspirer de deplacement_bas), 
la remise en place du main autour, les .h, le make et la définition des variables habituelles.
 Je reprendrais le reste plus tard, je ferai translation*/