#define REGLES_H

extern const int NBLINES;
extern const int NBCOLUMNS;

extern const bool DEBUG_MODE;

bool isEndgame(int mainGrid[NBLINES][NBCOLUMNS]);
int set_difficulty(int difficulty);