#define REGLES_H

extern const int NBLINES;
extern const int NBCOLUMNS;

extern const bool DEBUG_MODE;

bool isEndgame(int mainGrid[NBLINES][NBCOLUMNS],bool* inGame);

int setDifficulty(char* difficulty);

int setDelay(char* difficulty);

int setPointsperLine(char* difficulty);
