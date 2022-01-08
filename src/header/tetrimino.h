#define TETRIMINO_H

extern const int BLOCK_VIDE;
extern const int BLOCK_O; 
extern const int BLOCK_I; 
extern const int BLOCK_S; 
extern const int BLOCK_Z; 
extern const int BLOCK_L; 
extern const int BLOCK_J; 
extern const int BLOCK_T;

extern const int NBLINES;
extern const int NBCOLUMNS;

void initGrid(int grid[NBLINES][NBCOLUMNS]);

void setRandom(int* tetriminoID);

void downGridfromline(int mainGrid[NBLINES][NBCOLUMNS],int i);

int countLinesfull(int mainGrid[NBLINES][NBCOLUMNS]);

bool isDownfree(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void genTetrimino(int mobileGrid[NBLINES][NBCOLUMNS], int tetriminoID);

void goDown(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void goLeft(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void goRight(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void goBottom(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void putTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void turnTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void delay(int ms);