#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <assert.h>

#include "header/rules.h"
#include "header/gameUI.h"

const int BLOCK_VIDE = 0;
const int BLOCK_O = 1;  // Correspond au tétromino en forme de carré
const int BLOCK_I = 2;  // Correspond au tétromino en forme de bâton
const int BLOCK_S = 3;  // Correspond au tétromino en forme de biais inversé
const int BLOCK_Z = 4;  // Correspond au tétromino en forme de biais
const int BLOCK_L = 5;  // Correspond au tétromino en forme de L
const int BLOCK_J = 6;  // Correspond au tétromino en forme de L inversé
const int BLOCK_T = 7;  // Correspond au tétromino en forme de T

/* Cette fonction void remplit de 0 la grille passée en entrée. */
void initGrid(int grid[NBLINES][NBCOLUMNS]){
    for (int x = 0; x < NBLINES; x++){
        for (int y = 0; y < NBCOLUMNS; y++){
            grid[x][y] = 0;
        }
    }
}


/* Renvoie si une grille donnée est vide ou non */
bool isGridempty(int grid[NBLINES][NBCOLUMNS]){
    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++){
            if (grid[i][j] != BLOCK_VIDE) return false;
        }
    }
    return true;
}

/* Fonction qui génère un nombre aléatoire entre 1 et 8 en se basant sur rand() et la date */
void setRandom(int* tetriminoID){

    /* Comme random est dépendant de la machine, on ajoute des données de temps pour se rapprocher d'une génération vraiment aléatoire. */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int result = (tm.tm_year+tm.tm_mon+tm.tm_mday+tm.tm_hour+tm.tm_min+tm.tm_sec+rand())%7+1;

    /*Empêche de générer 2 fois de suite le même tetrimino*/
    while(result == *tetriminoID){
        result = (rand())%7+1;
    }

    *tetriminoID = result;
    return;
}

/*Génère un tetrimino en haut de la grille secondaire*/
void genTetrimino(int mobileGrid[NBLINES][NBCOLUMNS], int tetriminoID){

    /*Les blocs sont générés au milieu de la grille.*/
    int middle = NBCOLUMNS/2;

    if(tetriminoID == BLOCK_O){
        /* Correspond au tétromino en forme de carré */
        mobileGrid[0][middle]  = tetriminoID;
        mobileGrid[0][middle+1]= tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle+1]= tetriminoID;
    } else if(tetriminoID == BLOCK_I){
        /* Correspond au tétromino en forme de baton */
        mobileGrid[1][middle-2]= tetriminoID;
        mobileGrid[1][middle-1]= tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle+1]= tetriminoID;
    } else if (tetriminoID == BLOCK_S){
        /* Correspond au tétromino en forme de biais inversé */
        mobileGrid[0][middle+1]= tetriminoID;
        mobileGrid[0][middle]  = tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle-1]= tetriminoID;
    } else if (tetriminoID == BLOCK_Z){
        /* Correspond au tétromino en forme de biais */
        mobileGrid[0][middle-1]= tetriminoID;
        mobileGrid[0][middle]  = tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle+1]= tetriminoID;
    } else if (tetriminoID == BLOCK_L){
        /* Correspond au tétromino en forme de L */
        mobileGrid[0][middle+1]= tetriminoID;
        mobileGrid[1][middle+1]= tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle-1]= tetriminoID;
    } else if (tetriminoID == BLOCK_J){
        /* Correspond au tétromino en forme de L inversé */
        mobileGrid[0][middle-1]= tetriminoID;
        mobileGrid[1][middle-1]= tetriminoID;
        mobileGrid[1][middle]  = tetriminoID;
        mobileGrid[1][middle+1]= tetriminoID;
    } else if(tetriminoID == BLOCK_T){
        /* Correspond au tétromino en forme de T */
        mobileGrid[0][middle] = tetriminoID;
        mobileGrid[1][middle] = tetriminoID;
        mobileGrid[1][middle+1]=tetriminoID;
        mobileGrid[1][middle-1]=tetriminoID;
    }
    
    return ;
}

/* Vérifie si le bas du tetrimino est libre */
bool isDownfree(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){
    for(int i = NBLINES-1; i > 0 ; i--){
        for(int j = NBCOLUMNS-1; j >= 0; j--){
            if (mobileGrid[i][j] != BLOCK_VIDE){
                if(mainGrid[i+1][j] != BLOCK_VIDE){ // Si il y a un bloc en dessous dans mainGrid
                    return false;
                } else if (i == NBLINES-1){         // Atteint le bas de la grille
                    return false;
                }
            }
        }
    }
    return true;
}

/* Fait descendre d'une ligne la grille à partir d'une ligne donnée */
void downGridfromline(int mainGrid[NBLINES][NBCOLUMNS], int i){
    for (i = i; i > 0; i--){

        for (int j = 0; j < NBCOLUMNS; j++)
        {
            mainGrid[i][j] = mainGrid[i-1][j];
        }
    }
}

/* Vérifie si une ligne de la grille est pleine */
int countLinesfull(int mainGrid[NBLINES][NBCOLUMNS]){

    int nbLinesfull = 0;

    for (int i = 0; i < NBLINES; ++i){
        
        int temp = 0;

        /* Compte les blocs sur une ligne */
        for (int j = 0; j < NBCOLUMNS; ++j){
            if(mainGrid[i][j] != BLOCK_VIDE){
                temp++;
            }
        }
        
        /* Si la ligne est pleine, suppression */
        if(temp == NBCOLUMNS){
            blinkLine(i);
            downGridfromline(mainGrid, i);
            nbLinesfull++;
        }
    }

    return nbLinesfull;
}

/*Place le tetrimino d'une grille donnée à une autre. */
void putTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){

    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++){
            if(mobileGrid[i][j] != 0){
                mainGrid[i][j] = mobileGrid[i][j];
            }
        }
    }
    return;
}

/* Descend un bloc dans la grille lorsque c'est possible, si le bloc ne peut plus descendre, le tetrimino est placé */
void goDown(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){

    for(int i = NBLINES-1; i > 0; i--){  
        for(int j = NBCOLUMNS; j >= 0; j--){
            mobileGrid[i][j] = mobileGrid[i-1][j];
        }
    }

    /*Remplis la ligne du haut de bloc_VIDE*/
    for (int k = 0; k < NBCOLUMNS; k++){
        mobileGrid[0][k] = BLOCK_VIDE;
    }

    return;
}

/* Déplace un bloc vers la gauche dans la grille si possible */
void goLeft(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){
    for(int i = 0; i < NBLINES ; i++){
        for(int j = 0; j < NBCOLUMNS; j++){
            if (mobileGrid[i][j] != BLOCK_VIDE){
                if(mainGrid[i][j-1] != BLOCK_VIDE){
                    return;
                } else if (j == 0){
                    return;
                }
            }
        }
    }
    for(int i = 0; i < NBLINES; i++){
        for(int j = 0; j < NBCOLUMNS; j++){
            mobileGrid[i][j] = mobileGrid[i][j+1];
        }
        mobileGrid[i][NBCOLUMNS] = BLOCK_VIDE; //on remplis de bloc_VIDE sur la dernière colonne
    }

    return;
}

/* Déplace un bloc vers la droite dans la grille si possible */
void goRight(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){
    for(int i = 0; i < NBLINES ; i++){
        for(int j = 0; j < NBCOLUMNS; j++){
            if (mobileGrid[i][j] != BLOCK_VIDE){
                if(mainGrid[i][j+1] != BLOCK_VIDE){
                    return;
                } else if (j == NBCOLUMNS-1){
                    return;
                }
            }
        }
    }
    for(int i = 0; i < NBLINES; i++){
        for(int j = NBCOLUMNS-1; j > 0; j--){
            mobileGrid[i][j] = mobileGrid[i][j-1];
        }
        mobileGrid[i][0] = BLOCK_VIDE; // Remplit de bloc_VIDE sur la dernière colonne
    }

    return;
}

/* Descend un tétrimino le plus bas possible. Voir documentation pour plus de détails*/
void goBottom(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){

    if(isGridempty(mobileGrid)) return;  // Prévent d'une boucle infinie
    while(isDownfree(mainGrid, mobileGrid)){
        goDown(mainGrid, mobileGrid);
    }
    return;
}

/* Effectue la rotation d'un tetrimino dans le sens horaire si possible */
void turnTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]){

    /* Création d'une grille de simulation */
    int tempGrid[NBLINES][NBCOLUMNS];
    for (int i = 0; i < NBLINES; ++i){
        for (int j = 0; j < NBCOLUMNS; ++j)
        {
            tempGrid[i][j] = mobileGrid[i][j];
        }
    }

    /* Encadrement du tetrimino dans la grille */
    int iMin = NBLINES;
    int jMin = NBCOLUMNS;
    int iMax = 0;
    int jMax = 0;

    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++){
            if(tempGrid[i][j] != BLOCK_VIDE){
                if(i < iMin) iMin = i;
                if(i > iMax) iMax = i;
                if(j < jMin) jMin = j;
                if(j > jMax) jMax = j;
            }
        }
    }

    /* Calcul du milieu de la matrice pour se baser sur l'orientation */
    int iMiddle = (iMax+iMin)/2+1;
    int jMiddle = (jMax+jMin)/2+1;

    /* Extension de la matrice obtenu en matrice carré. Cherche la solution la plus proche du centre.
     * Agrandie en fonction de la taille disponible dans la grille et éviter un dépassement de tableau.
     */
    while(iMax-iMin != jMax-jMin){
        if(iMax-iMin > jMax-jMin){
            if(jMax-jMiddle > jMiddle-jMin){
                if(jMax < NBCOLUMNS-1) jMax++;
                else jMin--;
            }
            else {
                if(jMin > 0) jMin--;
                else jMax++;
            }
        } else
        if(iMax-iMin < jMax-jMin){
            if(iMax-iMiddle < iMiddle-iMin){
                if(iMax < NBLINES-1) iMax++;
                else iMin--;
            }
            else {
                if (iMin > 0) iMin--;
                else iMax++;
            }
        }
    }

    /* Inversement par la diagonale de la matrice */
    for (int i = 0; i < iMax-iMin+1; i++){
        for (int j = i; j < iMax-iMin+1; j++){
            int temp = tempGrid[iMin+i][jMin+j];
            tempGrid[iMin+i][jMin+j] = tempGrid[iMin+j][jMin+i];
            tempGrid[iMin+j][jMin+i] = temp;
        }
    }

    /* Inversement par la verticale de la matrice */
    for (int i = 0; i < iMax-iMin+1; i++){
        for (int j = 0; j < (iMax-iMin+1)/2; j++){
            int temp = tempGrid[iMin+i][jMin+j];
            tempGrid[iMin+i][jMin+j] = tempGrid[iMin+i][jMax-j];
            tempGrid[iMin+i][jMax-j] = temp;
        }
    }

    /* Vérifie si la place est disponible dans la grille de jeu, la fonction s'arrête si ce n'est pas le cas. */
    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++)
        {
            if(tempGrid[i][j] != BLOCK_VIDE){
                if(mainGrid[i][j] != BLOCK_VIDE) return;
            }
        }
    }

    /* Copie la rotation simulée dans la grille */
    for (int i = 0; i < NBLINES; ++i){
        for (int j = 0; j < NBCOLUMNS; ++j)
        {
            mobileGrid[i][j] = tempGrid[i][j];
        }
    }

    return;
}