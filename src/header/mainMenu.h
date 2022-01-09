#define MAINMENU_H

void initNcurses();

void drawMenu(int selection, int highScore, int lastScore);

void difficultyPicker(int* difficulty);

void gameModePicker(int* gameMode);

void drawGameModePicker(int selection);

void drawDifficultyPicker(int selection);

void drawHelp();

void drawCredits();

void animatedTitle(int frame);
