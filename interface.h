#define INTERFACE_H


void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow);

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, WINDOW *gridWindow,bool* inGame,int* score_counter);

void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow,bool* inGame,int score_counter);

void drawCommands();

void drawDifficulty(char difficulty);

void initUI();

void pause();

void blinkLine(int line);

void drawScore(int* score, int score_counter, int points_per_line);

void menuUI(char difficulty);

void drawTitle();

void selectDifficultyUI(char* res);

void endUI(bool* gameOn,bool*inGame);