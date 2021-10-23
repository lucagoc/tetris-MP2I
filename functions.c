#include <stdio.h>
#include <stdlib.h>


int* generation_bloc(int bloc[],int id,int x,int y,int id_couleur){
    int rouge=0;
    int bleu=1;
    if (id==2){
        bloc[0]=(x,y);
        bloc[1]=(x,y+1);
        bloc[2]=(x+1,y+1);
        bloc[3]=(x+1,y+1);
        bloc[4]=0;
    }
    return bloc;
}