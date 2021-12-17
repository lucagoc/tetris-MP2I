#define DEBUG_H

void affiche_debug(int movinggrid[nblignes][nbcolonnes], int grille[nblignes][nbcolonnes]);

extern const int bloc_DEBUG;

void debug_head(FILE* fp);
void debug_write_keypress(FILE* fp, char dir);
void debug_write_selection(FILE* fp, int imin, int jmin, int imax, int jmax);
FILE* debug_start();


