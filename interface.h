//#ifndef INTERFACE_H

#define INTERFACE_H

void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow);

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventaire, WINDOW *gridWindow,bool* inGame,int* score_counter);

void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow,bool* inGame,int score_counter);

void draw_commands();

void initUI();

void pause();

void blinkLine(int line);

void draw_score(int* score, int score_counter, int points_per_line);

void menu_ui();

void drawTitle();