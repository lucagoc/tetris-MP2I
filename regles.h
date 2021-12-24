#define REGLES_H

extern const int NBLINES;
extern const int NBCOLUMNS;

extern const bool DEBUG_MODE;

bool isEndgame(int mainGrid[NBLINES][NBCOLUMNS],bool* inGame);

int set_difficulty(int difficulty);

int set_delay(int difficulty);

int set_points_per_line(int difficulty);
