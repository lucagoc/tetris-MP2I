//#ifndef INTERFACE_H

#define INTERFACE_H

void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *fenetre);

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, WINDOW *fenetre);

void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *fenetre);

void initUI();

void pause();
