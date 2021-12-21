//#ifndef INTERFACE_H

#define INTERFACE_H

void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow);

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, WINDOW *gridWindow);

void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow);
void draw_commands();

void initUI();

void pause();
