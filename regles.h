#define REGLES_H

extern const int NBLINES;
extern const int NBCOLUMNS;

extern const bool DEBUG_MODE;

bool isEndgame(int mainGrid[NBLINES][NBCOLUMNS],bool* inGame);

int set_difficulty(char* difficulty);

int set_delay(char* difficulty);

int set_points_per_line(char* difficulty);
