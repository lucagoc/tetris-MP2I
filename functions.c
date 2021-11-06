#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

const int VIDE = 0;
const int O = 1; /* correspond au tétromino en forme de carré */
const int I = 2; /* correspond au tétromino en forme de baton */
const int S = 3; /* correspond au tétromino en forme de biais inversé */
const int Z = 4; /* correspond au tétromino en forme de biais */
const int L = 5; /* correspond au tétromino en forme de L */
const int J = 6; /* correspond au tétromino en forme de L inversé */
const int T = 7; /* correspond au tétromino en forme de T */

/* on définit ici des constantes pour attribuer les couleurs (sera utile lors de l'affichage avec ncurses) */
const int rouge = 0;
const int orange = 1;
const int jaune = 2;
const int vert = 3;
const int bleu = 4;
const int violet = 5;

void grille_vide(int grille[20][25]){
    for (int x=0;x<=19;x++){
        for (int y=0;y<=24;y++){
            grille[x][y]=0;
        }
    }
}
/* id_bloc correspond à un chiffre qui désigne tel ou tel bloc selon ce qui a été défini plus haut */
void generation_tetrimino(int bloc[5][2],int id_bloc,int x,int y,int id_couleur){
    if (id_bloc==1){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x ; bloc[1][1]=y+1 ;
        bloc[2][0]=x ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+1 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==2){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y ;
        bloc[3][0]=x+3 ; bloc[3][1]=y ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==3){
        bloc[0][0]=x+1 ; bloc[0][1]=y ;
        bloc[1][0]=x+2 ; bloc[1][1]=y ;
        bloc[2][0]=x ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+1 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==4){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+1 ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+2 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==5){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y+1 ;
        bloc[3][0]=x ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==6){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y ;
        bloc[3][0]=x+2 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==7){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y ;
        bloc[3][0]=x+1 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

}
/* on utilise ici 1 pour le moment pour dire que la case n'est pas vide, on s'occupera d'implémenter la couleur plus tard */
void tetrimino_dans_grille(int tetrimino[5][2],int grille[20][25]){
    for(int i=0; i<4;i++){
        int x_temp; int y_temp;
        x_temp=tetrimino[i][0];
        y_temp=tetrimino[i][1];
        grille[x_temp][y_temp] = 1;
    }
}

void affiche_grille(int grille[20][25],WINDOW *fenetre){
    for(int x=1;x<=18;x++){
        for (int y=1; y<=23;y++){
            if (grille[x][y]!=0){
                wmove(fenetre,x,y);
                wprintw(fenetre,"X");
            }
        }
    }
}