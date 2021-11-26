//#ifndef INTERFACE_H

#define INTERFACE_H


extern const int rouge;
extern const int orange;
extern const int jaune;
extern const int vert;
extern const int bleu;
extern const int violet; 


void affiche_grille(int grille[nblignes][nbcolonnes], WINDOW *fenetre);

void initialisation_interface();

