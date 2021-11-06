#ifndef FUNCTIONS_H

#define FUNCTIONS_H

const int VIDE;
const int O; 
const int I; 
const int S; 
const int Z; 
const int L; 
const int J; 
const int T; 


const int rouge;
const int orange;
const int jaune;
const int vert;
const int bleu;
const int violet;

void grille_vide(int grille[20][25]);

void generation_tetrimino(int bloc[5][2],int id_bloc,int x,int y,int id_couleur);

void tetrimino_dans_grille(int tetrimino[5],int grille[20][25]);

void affiche_grille(int grille[20][25],WINDOW *fenetre);



#endif