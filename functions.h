#ifndef FUNCTIONS_H

#define FUNCTIONS_H


extern const int VIDE;
extern const int O; 
extern const int I; 
extern const int S; 
extern const int Z; 
extern const int L; 
extern const int J; 
extern const int T; 


extern const int rouge;
extern const int orange;
extern const int jaune;
extern const int vert;
extern const int bleu;
extern const int violet; 




void grille_vide(int grille[20][25]);

void generation_tetrimino(int bloc[5][2],int id_bloc,int x,int y,int id_couleur);

void tetrimino_dans_grille(int tetrimino[5][2],int grille[20][25]);

void affiche_grille(int grille[20][25],WINDOW *fenetre);

void deplacement_bas(int bloc[5][2],int grille[20][25]);

void translation(int bloc[5][2], char lor, int grille[20][25]);

void delai(int nb_secondes);



#endif
