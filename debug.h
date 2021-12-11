#define DEBUG_H

void affiche_debug(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void debug_head(FILE* fp);
void debug_write_deplacement(FILE* fp, char dir);
FILE* debug_start();

