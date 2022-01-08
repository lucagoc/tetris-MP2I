#define RULES_H

extern const int NBLINES;
extern const int NBCOLUMNS;


void setDifficulty(int difficulty, int* speedCycle);

bool isGridfull(int mainGrid[NBLINES][NBCOLUMNS]);

void scoring(int nbLinesfull, int difficulty, int* score);

int timer(int timeStarted);

void switchInventory(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int* tetriminoID, int* inventory);