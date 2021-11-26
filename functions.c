#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

const int bloc_VIDE = 0;
const int bloc_O = 1; /* correspond au tétromino en forme de carré */
const int bloc_I = 2; /* correspond au tétromino en forme de baton */
const int bloc_S = 3; /* correspond au tétromino en forme de biais inversé */
const int bloc_Z = 4; /* correspond au tétromino en forme de biais */
const int bloc_L = 5; /* correspond au tétromino en forme de L */
const int bloc_J = 6; /* correspond au tétromino en forme de L inversé */
const int bloc_T = 7; /* correspond au tétromino en forme de T */

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
    if (id_bloc==bloc_O){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x ; bloc[1][1]=y+1 ;
        bloc[2][0]=x ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+1 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_I){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y ;
        bloc[3][0]=x+3 ; bloc[3][1]=y ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_S){
        bloc[0][0]=x+1 ; bloc[0][1]=y ;
        bloc[1][0]=x+2 ; bloc[1][1]=y ;
        bloc[2][0]=x ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+1 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_Z){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+1 ; bloc[2][1]=y+1 ;
        bloc[3][0]=x+2 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_L){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y+1 ;
        bloc[3][0]=x ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_J){
        bloc[0][0]=x ; bloc[0][1]=y ;
        bloc[1][0]=x+1 ; bloc[1][1]=y ;
        bloc[2][0]=x+2 ; bloc[2][1]=y ;
        bloc[3][0]=x+2 ; bloc[3][1]=y+1 ;
        bloc[4][0]=id_couleur;
    }

    else if (id_bloc==bloc_T){
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



void deplacement_bas(int bloc[5][2],int grille[20][25]){
    for(int i=0;i<4;i++){
        if(bloc[i][1]==24){ /*Si le petit cube du bloc est situé sur la ligne du bas*/
            tetrimino_dans_grille(bloc,grille); /*Alors on place le bloc !*/
        } else if (!(grille[bloc[0][i]-1][bloc[1][i]]==0)){ /*Si le petit cube du bloc n'est pas situé au-dessus d'un espace libre*/
            tetrimino_dans_grille(bloc,grille); /*Alors on place le bloc !*/
        }
    } /*Si tout s'est bien passé jusqu'à cette étape, alors on translate tout*/
    for(int i=0;i<4;i++){
       bloc[0][i]-=1;
    }
}

/*Cette fonction permet de vérifier si le bloc actuellement sélectionné peut subir une translation horizontale*/

void translation(int bloc[5][2], char lor, int grille[20][25]){ /*Le caractère lor signifie "Left or right", il permet de savoir si l'utilisateur veut faire sa translation à gauche ou à droite*/
    if(lor=='l'){ /*Si l'utilisateur souhaite faire sa translation vers la gauche, lor vaudra alors 'l' (left)*/
        for(int i=0;i<4;i++){
            if(bloc[i][0]==0){ /*Si le tetromino est situé sur la ligne à gauche de l'arène de jeu, il ne peut pas bouger à gauche*/
                return; /*La fonction étant un void, on ne renvoie rien. La ligne ici est juste pour montrer que le cas où le tetrimino est au bord est étudié.*/
            } else if (!(grille[bloc[i][0]-1][bloc[i][1]]==0)){ /*Cette ligne permet de vérifier si il n'y a aucun tetrimino situé à gauche du bloc actuel.*/
                return;
            } /*Ce sont les seuls cas de figure dans lesquels le tetromino ne peut pas bouger vers la gauche. Dans le vrai Tetris, le tetromino peut bouger, même si il est situé au-dessus d'un bloc qui est censé l'immobiliser.*/
        }
        for(int i=0;i<4;i++){ /*Cette boucle permet, une fois que l'on a vérifié, d'effectuer la translation sur chacun des blocs*/
            bloc[i][0]-=1;
        } /*Fin de la translation gauche.*/
    } else { /*Maintenant, étudions le cas "Translation à droite". Les commentaires sont les mêmes que ceux de gauche*/
        for(int i=0;i<4;i++){
            if(bloc[i][0]==10){
                return;
            } else if (!(grille[bloc[i][0]+1][bloc[i][1]]==0)){
                return;
            }
        }
        for(int i=0;i<4;i++){
            bloc[i][0]+=1;
        } /*Fin de la translation droite.*/
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
