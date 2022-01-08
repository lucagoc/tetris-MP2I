#define DEBUG_H

extern const int BLOCK_DEBUG;
extern const bool DEBUG_MODE;

void drawDebug(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void genDebugtetrimino(int mobileGrid[NBLINES][NBCOLUMNS]);

