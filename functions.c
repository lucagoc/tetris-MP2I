#include <stdio.h>
#include <stdlib.h>

const int VIDE = 0;
const int O = 1;
const int I = 2;
const int S = 3;
const int Z = 4;
const int L = 5;
const int J = 6;
const int T = 7;

/*Remplis la grille de VIDE*/
void initialisation_bloc(int* bloc, int n){
    for (int i = 0; i <= n; i++){
        bloc[i] = VIDE;
    }
}

/*Fonction qui alloue de la mémoire pour une taille de grille en 2D donnée*/
int* allocation(int n){
    int *p = (int*)malloc(n*n*sizeof(*p));
    return p;
}

/*Attention les matrices utilisées sont des matrices applaties car plus simple à programmer. Par exemple un t[3][3] devient un t[9] et les cases sont:
    [0][1][2]
    [3][4][5]
    [6][7][8]
*/

/*Fonction de génération de bloc dans la mémoire selon un ID donnée*/
int* generation_bloc(int id){

    if (id == VIDE){
        return NULL;
        /*retourne une erreur au cas où*/
    } 

    /*Le tetromino I a la articularité d'être sur une grille de 5x5 et non de 3x3 à cause de sa longueur, on le différencie donc des autres cas.*/
    else if (id == I){
        int n = 5;
        int* bloc = allocation(n); // Allocation de la mémoire
        initialisation_bloc(bloc, n); //Initialisation de la grille du tetromino par VIDE

        /*Attribution des valeurs pour le former*/
        bloc[2] = I;
        bloc[7] = I;
        bloc[12] = I;
        bloc[17] = I;
        bloc[22] = I;

        return bloc;
    }

    /*Même chose pour tous les autres tetromino en grille de 3x3*/
    else {
        int n = 3;
        int* bloc = allocation(n);
        initialisation_bloc(bloc, n);

        if (id == O){ //bloc O
            bloc[1] = O;
            bloc[2] = O;
            bloc[4] = O;
            bloc[5] = O;
        } else if (id == S){ //bloc S
            bloc[1] = S;
            bloc[2] = S;
            bloc[3] = S;
            bloc[4] = S;
        } else if (id == Z){ //bloc Z
            bloc[0] = Z;
            bloc[1] = Z;
            bloc[4] = Z;
            bloc[5] = Z;
        } else if (id == L){ //bloc L
            bloc[0] = L;
            bloc[3] = L;
            bloc[6] = L;
            bloc[7] = L;
        } else if (id == J){ //bloc J
            bloc[2] = J;
            bloc[5] = J;
            bloc[7] = J;
            bloc[8] = J;
        } else if (id == T){ //bloc T
            bloc[0] = T;
            bloc[1] = T;
            bloc[2] = T;
            bloc[4] = T;
        }

        return bloc;
    }

}