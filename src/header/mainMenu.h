#define MAINMENU_H

void initNcurses();

void drawMenu(int selection, int highScore);

void difficultyPicker(int* difficulty);

void drawHelp();

void drawCredits();

void animatedTitle(int frame);