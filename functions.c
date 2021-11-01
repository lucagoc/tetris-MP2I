#include <stdio.h>
#include <stdlib.h>
void grille_vide(int grille[20][25]){
    for (int x=0;x<=19;x++){
        for (int y=0;y<=24;y++){
            grille[x][y]=0;
        }
    }
}

void generation_bloc(int bloc[5],int id,int x,int y,int id_couleur){
    int rouge=0;
    int bleu=1;
    if (id==2){
        bloc[0]=(x,y);
        bloc[1]=(x,y+1);
        bloc[2]=(x+1,y+1);
        bloc[3]=(x+1,y+1);
        bloc[4]=0;
    }
}