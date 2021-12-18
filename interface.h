//#ifndef INTERFACE_H

#define INTERFACE_H


void affiche_grille(int grille[nblignes][nbcolonnes], WINDOW *fenetre);

void draw_interface(int grille[nblignes][nbcolonnes], int movinggrid[nblignes][nbcolonnes], WINDOW *fenetre);

void ghost_bloc(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes], WINDOW *fenetre);

void initialisation_interface();

void pause();
