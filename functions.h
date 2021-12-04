#ifndef FUNCTIONS_H

#define FUNCTIONS_H


extern const int bloc_VIDE;
extern const int bloc_O; 
extern const int bloc_I; 
extern const int bloc_S; 
extern const int bloc_Z; 
extern const int bloc_L; 
extern const int bloc_J; 
extern const int bloc_T; 

extern const int nblignes;
extern const int nbcolonnes;


void grille_vide(int grille[nblignes][nbcolonnes]);

void generation_tetrimino(int bloc[5][2],int id_bloc,int x,int y,int id_couleur);

void tetrimino_dans_grille(int tetrimino[5][2],int grille[nblignes][nbcolonnes]);

void deplacement_bas(int bloc[5][2],int grille[nblignes][nbcolonnes]);

void translation(int bloc[5][2], char lor, int grille[nblignes][nbcolonnes]);

void delai(int nb_secondes);



#endif
