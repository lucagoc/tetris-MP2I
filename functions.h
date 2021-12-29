
#ifndef FUNCTIONS_H

#define FUNCTIONS_H


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

void isGridempty(int grid[NBLINES][NBCOLUMNS]);

int setRandom(int tetriminoID);

void downGridfromline(int mainGrid[NBLINES][NBCOLUMNS],int i);

void checkLinefull(int mainGrid[NBLINES][NBCOLUMNS],int* score_counter);

int genTetrimino(int mobileGrid[NBLINES][NBCOLUMNS], int tetriminoID);

int goDown(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int tetriminoID, int timeOut,bool* inGame,int* score_counter);

void goLeft(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void goRight(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void goBottom(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS],bool* inGame, int* score_counter);

int putTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int tetriminoID, int timeOut, bool* inGame, int* score_counter);

void turnTetrimino(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS]);

void delay(int ms);




#endif
