
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


void init_grille(int grille[nblignes][nbcolonnes]);

void grille_vide(int grille[nblignes][nbcolonnes]);

void ligne_pleine(int grille[nblignes][nbcolonnes]);

void generation_tetrimino(int movinggrid[nblignes][nbcolonnes]);

void deplacement_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void deplacement_gauche(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void deplacement_droite(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void teleportation_bas(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void delai(int nb_secondes);

void placer(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void rotation(int movinggrid[nblignes][nbcolonnes],int grille[nblignes][nbcolonnes]);

void inventaire(int movinggrid[nblignes][nbcolonnes]);




#endif
