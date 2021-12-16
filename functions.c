#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "regles.h"
#include "debug.h"

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
void generation_tetrimino(int movinggrid[nblignes][nbcolonnes]){
    int id_bloc = (rand()%7)+1; // Génération d'un bloc random. La fonction rand() n'ayant pas de max, on utilise un modulo 8. On veut aussi ne pas obtenir la valeur 0.
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


void ligne_pleine(int grille[nblignes][nbcolonnes]){
    bool ligne_pleine=true;
    for(int i=0;i<nbcolonnes;i++){
        if (grille[nblignes-1][i]==0){
            ligne_pleine=false;
        }
    }
    if (ligne_pleine){
        for(int i=0;i<nbcolonnes;i++){
            grille[nblignes-1][i]=0;
        }
        for(int i=nblignes-1;i>0;i--){
            for(int j=nbcolonnes; j>0;j--){
                if (grille[i][j]!=0){
                    grille[i+1][j]=grille[i][j];
                }
            }
        }
    }
}

void placer(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    int temp[4][2];
    int x=0;
    for (int i = 0; i < nblignes; i++){
        for (int j = 0; j < nbcolonnes; j++){
            if(movinggrid[i][j] != 0){
                grille[i][j]=movinggrid[i][j];
            }
        }
    }
    init_grille(movinggrid);
    endgame(grille);//avant de placer le tetrimino suivant, on vérifie si la première ligne n'est pas occupée par un bloc, si c'est le cas, on termine la partie(et le programme pour l'instant)
    ligne_pleine(grille);//si la ligne du bas est pleine, on la vide et on fait descendre tous les autres tertiminos d'une ligne
    generation_tetrimino(movinggrid); //génère un tetrimino une fois l'autre placé.
    return;
}

/*Cette fonction permet de descendre un bloc vers le bas lorsque c'est possible*/
void deplacement_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    for(int i = nblignes-1; i > 0 ; i--){ /*Cette boucle balaie toutes les lignes*/
        for(int j = nbcolonnes-1; j >= 0; j--){ /*Et celle-ci toutes les colonnes*/
            if (movinggrid[i][j] != bloc_VIDE){
                if(grille[i+1][j] != bloc_VIDE){/*Si le carré dans 'grille' juste au-dessous de celui qu'on vient de détecter dans 'movinggrid' n'est pas vide, on ne peut pas descendre*/
                    placer(movinggrid,grille); /*Donc on place le bloc dans la grille*/
                    return;
                } else if (i == nblignes-1){
                    placer(movinggrid,grille); /*Et si on a atteint la ligne du bas, le bloc ne peut plus descendre, donc on le place dans 'grille'*/
                    return;
                }
            }
        }
    }
    for(int i = nblignes-1; i > 0; i--){ /*Cette boucle balaie toutes les lignes*/
        for(int j = nbcolonnes; j >= 0; j--){ /*Et celle-ci toutes les colonnes. Pour éviter de descendre plusieurs fois un seul bloc, le scan de 'movinggrid' se fait du bas vers le haut*/
            movinggrid[i][j] = movinggrid[i-1][j];
        }
    }
    for (int k = 0; k < nbcolonnes; k++){ // Remplis la ligne du haut de bloc_VIDE
        movinggrid[0][k] = bloc_VIDE;
    }
    return;
}

void deplacement_gauche(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    for(int i = 0; i < nblignes ; i++){
        for(int j = 0; j < nbcolonnes; j++){
            if (movinggrid[i][j] != bloc_VIDE){
                if(grille[i][j-1] != bloc_VIDE){ /*vérifie si le bloc à gauche dans grille contient un bloc*/
                    return; /*Donc on ne fait rien*/
                } else if (j == 0){
                    return; /*Et si on a atteint la ligne de gauche, on ne fait rien*/
                }
            }
        }
    }
    for(int i = 0; i < nblignes; i++){
        for(int j = 0; j < nbcolonnes; j++){
            movinggrid[i][j] = movinggrid[i][j+1];
        }
        movinggrid[i][nbcolonnes] = bloc_VIDE; //on remplis de bloc_VIDE sur la dernière colonne
    }
    return;
}

void deplacement_droite(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    for(int i = 0; i < nblignes ; i++){
        for(int j = 0; j < nbcolonnes; j++){
            if (movinggrid[i][j] != bloc_VIDE){
                if(grille[i][j+1] != bloc_VIDE){ /*vérifie si le bloc à droite dans grille contient un bloc*/
                    return; /*Donc on ne fait rien*/
                } else if (j == nbcolonnes-1){
                    return; /*Et si on a atteint la ligne de droite, on ne fait rien*/
                }
            }
        }
    }
    for(int i = 0; i < nblignes; i++){
        for(int j = nbcolonnes-1; j > 0; j--){
            movinggrid[i][j] = movinggrid[i][j-1];
        }
        movinggrid[i][0] = bloc_VIDE; //on remplit de bloc_VIDE sur la dernière colonne
    }
    return;
}

void teleportation_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){
    bool descend = true;
    while(descend){
        for (int i = 0; i < nblignes; i++){
            for (int j = 0; j < nbcolonnes; j++){
                if (movinggrid[i][j] != bloc_VIDE){
                    if(grille[i+1][j] != bloc_VIDE){/*Si le carré dans 'grille' juste au-dessous de celui qu'on vient de détecter dans 'movinggrid' n'est pas vide, on ne peut pas descendre*/
                        placer(movinggrid,grille); /*Donc on place le bloc dans la grille*/
                        descend = false;
                    } else if (i == nblignes-1){
                        placer(movinggrid,grille); /*Et si on a atteint la ligne du bas, le bloc ne peut plus descendre, donc on le place dans 'grille'*/
                        descend = false;
                    }
                }
            }
        }
        deplacement_bas(movinggrid,grille);
    }
    return;
}

void rotation(int movinggrid[nblignes][nbcolonnes],int grille[nblignes][nbcolonnes]){
    for (int i = 0; i < nblignes; i++){
        for (int j = 0; j < nbcolonnes; j++){
            if (movinggrid[i][j]!=0){
                movinggrid[j][-i]=movinggrid[i][j];

                movinggrid[i][j]=0;
            }
        }
    }
}

void delai(int nb_secondes)
{
    clock_t temps = clock();
    while (clock() < temps + 1000*nb_secondes);
}




/*Ce qui reste à faire : L'étude du cas pour translation (il suffit de s'inspirer de deplacement_bas), 
la remise en place du main autour, les .h, le make et la définition des variables habituelles.
 Je reprendrais le reste plus tard, je ferai translation*/