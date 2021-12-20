#define DEBUG_H

extern const int BLOCK_DEBUG;

void drawDebug(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void printLogdate(FILE* fp);

void printLogkey(FILE* fp, char dir);

void genDebugtetrimino(int mobileGrid[NBLINES][NBCOLUMNS]);

FILE* initLogfile();
