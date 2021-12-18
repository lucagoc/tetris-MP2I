#define DEBUG_H

extern const int bloc_DEBUG;

void affiche_debug(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

void debug_head(FILE* fp);

void debug_write_keypress(FILE* fp, char dir);

void debug_write_selection(FILE* fp, int imin, int jmin, int imax, int jmax);

void debug_tetrimino(int grille[nblignes][nbcolonnes]);

FILE* debug_start();


