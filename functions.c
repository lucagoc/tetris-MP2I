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


/*Cette fonction void permet de remplir de 0 la grille passée en entrées.*/
void init_grille(int grille[nblignes][nbcolonnes]){
    for (int x = 0; x < nblignes; x++){
        for (int y = 0; y < nbcolonnes; y++){
            grille[x][y] = 0;
        }
    }
}

bool grille_vide(int grille[nblignes][nbcolonnes]){
    for (int i = 0; i < nblignes; i++){
        for (int j = 0; j < nbcolonnes; j++){
            if (grille[i][j] != bloc_VIDE) return false;
        }
    }
    return true;
}

/*Génère un nombre aléatoire en se basant sur rand() et la date*/
int genRandom(int id_bloc){
    /*Comme random est dépendant de la machine, on ajoute des données de temps pour augmenter l'effet aléatoire.*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int resultat = (tm.tm_year+tm.tm_mon+tm.tm_mday+tm.tm_hour+tm.tm_min+tm.tm_sec+rand())%7+1;
    while(resultat == id_bloc){
        resultat = (rand())%7+1;
    }
    return resultat;
}

/*Cette fonction permet de placer un tetrimino directement prêt en haut de la grille secondaire*/
int generation_tetrimino(int movinggrid[nblignes][nbcolonnes], int id_bloc){

    /*Les bloc sont généré au milieu de la grille.*/
    int milieuC = nbcolonnes/2;

    /*les différents if correspondent à une disjonction de cas*/
    if(id_bloc == bloc_O){
        /* correspond au tétromino en forme de carré */
        movinggrid[0][milieuC]=id_bloc;
        movinggrid[0][milieuC+1]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
    } else if(id_bloc == bloc_I){
        /* correspond au tétromino en forme de baton */
        movinggrid[1][milieuC-2]=id_bloc;
        movinggrid[1][milieuC-1]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
    } else if (id_bloc == bloc_S){
        /* correspond au tétromino en forme de biais inversé */
        movinggrid[0][milieuC+1]=id_bloc;
        movinggrid[0][milieuC]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC-1]=id_bloc;
    } else if (id_bloc == bloc_Z){
        /* correspond au tétromino en forme de biais */
        movinggrid[0][milieuC-1]=id_bloc;
        movinggrid[0][milieuC]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
    } else if (id_bloc == bloc_L){
        /* correspond au tétromino en forme de L */
        movinggrid[0][milieuC+1]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC-1]=id_bloc;
    } else if (id_bloc == bloc_J){
        /* correspond au tétromino en forme de L inversé */
        movinggrid[0][milieuC-1]=id_bloc;
        movinggrid[1][milieuC-1]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
    } else if(id_bloc == bloc_T){
        /* correspond au tétromino en forme de T */
        movinggrid[0][milieuC]=id_bloc;
        movinggrid[1][milieuC]=id_bloc;
        movinggrid[1][milieuC+1]=id_bloc;
        movinggrid[1][milieuC-1]=id_bloc;
    }
    
    /*permet de stocker le nombre pour la réserve*/
    return id_bloc;
}


void ligne_pleine(int grille[nblignes][nbcolonnes]){
    bool ligne_pleine = true;
    for(int  i = 0; i < nbcolonnes; i++){
        if (grille[nblignes-1][i] == 0){
            ligne_pleine = false;
        }
    }
    if (ligne_pleine){
        for(int i = 0; i < nbcolonnes; i++){
            grille[nblignes-1][i] = 0;
        }
        for(int i = nblignes-1; i > 0; i--){
            for(int j = nbcolonnes; j > 0; j--){
                if (grille[i][j] != 0){
                    grille[i+1][j] = grille[i][j];
                }
            }
        }
    }
}

int placer(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes], int id_bloc){
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
    return generation_tetrimino(movinggrid, genRandom(id_bloc)); //génère un tetrimino une fois l'autre placé.
}

/*Cette fonction permet de descendre un bloc vers le bas lorsque c'est possible*/
int deplacement_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes], int id_bloc){
    for(int i = nblignes-1; i > 0 ; i--){ /*Cette boucle balaie toutes les lignes*/
        for(int j = nbcolonnes-1; j >= 0; j--){ /*Et celle-ci toutes les colonnes*/
            if (movinggrid[i][j] != bloc_VIDE){
                if(grille[i+1][j] != bloc_VIDE){/*Si le carré dans 'grille' juste au-dessous de celui qu'on vient de détecter dans 'movinggrid' n'est pas vide, on ne peut pas descendre*/
                    return placer(movinggrid, grille, id_bloc); /*Donc on place le bloc dans la grille*/
                } else if (i == nblignes-1){
                    return placer(movinggrid, grille, id_bloc); /*Et si on a atteint la ligne du bas, le bloc ne peut plus descendre, donc on le place dans 'grille'*/
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
    return id_bloc;
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

    if(grille_vide(movinggrid)) return; // Evite une boucle infinie
    bool descend = true;
    while(descend){
        for (int i = 0; i < nblignes; i++){
            for (int j = 0; j < nbcolonnes; j++){
                if (movinggrid[i][j] != bloc_VIDE){
                    if(grille[i+1][j] != bloc_VIDE){/*Si le carré dans 'grille' juste au-dessous de celui qu'on vient de détecter dans 'movinggrid' n'est pas vide, on ne peut pas descendre*/
                        return;
                    } else if (i == nblignes-1){
                        return;
                    }
                }
            }
        }
        deplacement_bas(movinggrid,grille,0);
    }
}

void delai(int nb_secondes)
{
    clock_t temps = clock();
    while (clock() < temps + 1000*nb_secondes);
}

void rotation(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]){

    /*Encadrement du tetrimino dans la grille*/
    int imin = nblignes;
    int jmin = nbcolonnes;
    int imax = 0;
    int jmax = 0;

    for (int i = 0; i < nblignes; i++){
        for (int j = 0; j < nbcolonnes; j++){
            if(movinggrid[i][j] != bloc_VIDE){
                if(i < imin) imin = i;
                if(i > imax) imax = i;
                if(j < jmin) jmin = j;
                if(j > jmax) jmax = j;
            }
        }
    }

    /*Calcul du milieu de la matrice pour se baser sur l'orientation*/
    int imilieu = (imax+imin)/2+1;
    int jmilieu = (jmax+jmin)/2+1;

    /*Extension de la matrice obtenu en matrice carré. Cherche la solution la plus proche du centre.
     *Agrandie en fonction de la taille disponible dans la grille et éviter un dépassement de tableau.
     */
    while(imax-imin != jmax-jmin){
        if(imax-imin > jmax-jmin){
            if(jmax-jmilieu > jmilieu-jmin){
                if(jmax < nbcolonnes-1) jmax++;
                else jmin--;
            }
            else {
                if(jmin > 0) jmin--;
                else jmax++;
            }
        } else
        if(imax-imin < jmax-jmin){
            if(imax-imilieu < imilieu-imin){
                if(imax < nblignes-1) imax++;
                else imin--;
            }
            else {
                if (imin > 0) imin--;
                else imax++;
            }
        }
    }

    /*Vérification de la disponibilité dans la grille des emplacements utilisés.*/
    for (int i = imin; i <= imax; i++){
        for (int j = jmin; j <= jmax; j++){
            if(grille[i][j] != bloc_VIDE) return;
        }
    }

    //Inversement par la diagonale de la matrice
    for (int i = 0; i < imax-imin+1; i++){
        for (int j = i; j < imax-imin+1; j++){
            int temp = movinggrid[imin+i][jmin+j];
            movinggrid[imin+i][jmin+j] = movinggrid[imin+j][jmin+i];
            movinggrid[imin+j][jmin+i] = temp;
        }
    }

    //Inversement par la verticale de la matrice
    for (int i = 0; i < imax-imin+1; i++){
        for (int j = 0; j < (imax-imin+1)/2; j++){
            int temp = movinggrid[imin+i][jmin+j];
            movinggrid[imin+i][jmin+j] = movinggrid[imin+i][jmax-j];
            movinggrid[imin+i][jmax-j] = temp;
        }
    }

    return;
}

void inventaire(int movinggrid[nblignes][nbcolonnes]){
    return;
}
