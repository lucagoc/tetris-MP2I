#include <stdio.h>
#include <ncurses.h>
#include <time.h>

int main(){

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    printw("%d",generation_bloc(2,4,4,0));
    
    refresh();
    getch();

    endwin();


    /*cbreak();*/

    return 0;

}
   