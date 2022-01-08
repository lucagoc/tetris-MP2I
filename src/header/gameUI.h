#define GAMEUI_H

void blinkLine(int line);

void drawGame(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, int score, int timer, int difficulty, WINDOW *gridWindow);

void pause();