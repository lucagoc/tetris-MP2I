#define INTERFACE_H


void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow);

void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventory, WINDOW *gridWindow,bool* inGame,int* score_counter);

void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow,bool* inGame,int score_counter);

void draw_commands();

void draw_difficulty(char difficulty);

void initUI();

void pause();

void blinkLine(int line);

void draw_score(int* score, int score_counter, int points_per_line);

void menu_ui(char difficulty);

void drawTitle();

void select_difficulty_ui(char* res);

void end_ui(bool* gameOn,bool*inGame);