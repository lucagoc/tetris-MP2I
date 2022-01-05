#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include "regles.h"
#include "debug.h"
#include "tetrimino.h"


/*Affiche la grille de jeu */
void drawGrid(int grid[NBLINES][NBCOLUMNS], WINDOW *gridWindow){
    for(int x = 2; x < NBLINES; x++){
        for (int y = 0; y < NBCOLUMNS; y++){
            wmove(gridWindow,x-1,(y*2)+1);

            /*Implémentation des couleurs selon le type du bloc*/
            if(grid[x][y] == BLOCK_O){
                wattron(gridWindow, COLOR_PAIR(BLOCK_O));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_O));
            } else if(grid[x][y] == BLOCK_I){
                wattron(gridWindow, COLOR_PAIR(BLOCK_I));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_I));
            } else if(grid[x][y] == BLOCK_S){
                wattron(gridWindow, COLOR_PAIR(BLOCK_S));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_S));
            } else if(grid[x][y] == BLOCK_Z){
                wattron(gridWindow, COLOR_PAIR(BLOCK_Z));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_Z));
            } else if(grid[x][y] == BLOCK_L){
                wattron(gridWindow, COLOR_PAIR(BLOCK_L));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_L));
            } else if(grid[x][y] == BLOCK_J){
                wattron(gridWindow, COLOR_PAIR(BLOCK_J));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_J));
            } else if(grid[x][y] == BLOCK_T){
                wattron(gridWindow, COLOR_PAIR(BLOCK_T));
                wprintw(gridWindow,"  ");
                wattroff(gridWindow, COLOR_PAIR(BLOCK_T));
            } else if(grid[x][y] == BLOCK_DEBUG){
                wprintw(gridWindow,"{}");
            }
        }
    }

    return;
}

/*Affiche la prévisualisation de l'emplacement des tetrimino*/
void drawGhostblocks(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], WINDOW *gridWindow, bool* inGame,int* score_counter){

    /*Copie de la mobileGrid*/
    int tempGrid[NBLINES][NBCOLUMNS];
    for (int i = 0; i < NBLINES; i++){
        for (int j = 0; j < NBCOLUMNS; j++){
            tempGrid[i][j] = mobileGrid[i][j];
        }
    }

    goBottom(mainGrid, tempGrid,inGame,score_counter);
    
    /*Affichage des ghostblocs*/
    for(int x = 2; x < NBLINES; x++){
        for (int y = 0; y < NBCOLUMNS; y++){
            if(tempGrid[x][y] != 0) {
                wmove(gridWindow,x-1,(y*2)+1);
                wprintw(gridWindow,"[]");
            }
        }
    }

    return;
}

/* Affiche le score */
void draw_score(int* score, int score_counter, int points_per_line){
    *score += score_counter * points_per_line;
    move(19,NBCOLUMNS+15);
    printw("Score : %d\n",*score);

    return;
}

/*Affiche le l'interface du jeu.*/
void drawUI(int mainGrid[NBLINES][NBCOLUMNS], int mobileGrid[NBLINES][NBCOLUMNS], int inventaire, WINDOW *gridWindow,bool* inGame,int* score_counter){

    werase(gridWindow); //efface la frame précédente

    box(gridWindow, 0, 0);
    drawGrid(mainGrid, gridWindow);
    drawGhostblocks(mainGrid, mobileGrid, gridWindow,inGame,score_counter);
    drawGrid(mobileGrid, gridWindow);

    /*Affichage de celui qui est stocké*/
    move(17, NBCOLUMNS+26);
    printw("%d", inventaire);

    if (DEBUG_MODE){
        drawDebug(mobileGrid, mainGrid);
    }

    wrefresh(gridWindow);
    refresh();
}

/*Affiche les touches pour jouer*/
void draw_commands(){

    move(1,NBCOLUMNS+15);
    printw("Descente instantanée : Flèche du haut");
    move(3,NBCOLUMNS+15);
    printw("Gauche : Flèche de gauche");
    move(5,NBCOLUMNS+15);
    printw("Droite : Flèche du droite");
    move(7,NBCOLUMNS+15);
    printw("Bas : Flèche du bas");
    move(9,NBCOLUMNS+15);
    printw("Rotation : D");
    move(11,NBCOLUMNS+15);
    printw("Pause : P");
    move(13,NBCOLUMNS+15);
    printw("Quitter le jeu : Q");
    move(15,NBCOLUMNS+15);
    printw("Touche Réserve : S");
    move(17,NBCOLUMNS+15);
    printw("Réserve : ");
    refresh();

    return;
}

/*Applique les propriétés de l'affichage de nscurses*/
void initUI(){

	initscr();  // Initialise l'affichage ncurses
    start_color();  // Active la palette de couleur

    /*Création des palettes de couleurs*/
    init_pair(BLOCK_O, COLOR_WHITE, COLOR_YELLOW);
    init_pair(BLOCK_I, COLOR_WHITE, COLOR_CYAN);
    init_pair(BLOCK_S, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLOCK_Z, COLOR_WHITE, COLOR_RED);
    init_pair(BLOCK_L, COLOR_WHITE, COLOR_WHITE);
    init_pair(BLOCK_J, COLOR_WHITE, COLOR_BLUE);
    init_pair(BLOCK_T, COLOR_WHITE, COLOR_MAGENTA);


    curs_set(0);  // Cache le curseur
    noecho();  // Cache les touches pressées
    refresh();

    return;
}

/* Mets le jeu en pause en cachant l'affichage */
void pause(){
    
    bool inPause = true;
    WINDOW *pauseWindow = newwin(NBLINES,(NBCOLUMNS*2)+2, 0, 0);
    box(pauseWindow, 0, 0);
    wmove(pauseWindow, 10, 7);
    wprintw(pauseWindow, "En pause");
    wrefresh(pauseWindow);
    while(inPause){
        int key = getch();
        if(key != ERR){
            inPause = false;
        }
    }
    
    return;
}

/* Affiche un clignotement sur une ligne donnée */
void blinkLine(int line){
    for(int n = 0; n < 5; n++){

        attron(COLOR_PAIR(BLOCK_L));
        for (int j = 0; j < NBCOLUMNS; j++){
            move(line-1, (j*2)+1);
            printw("  ");
        }
        refresh();
        attroff(COLOR_PAIR(BLOCK_O));

        delay(40000);

        for (int j = 0; j < NBCOLUMNS; j++){
            move(line-1, (j*2)+1);
            printw("  ");
        }
        refresh();
        attroff(COLOR_PAIR(BLOCK_VIDE));

        delay(40000);
    }

    return;
}

/* Affiche le niveau de difficulté sélectionné par le joueur */
void draw_difficulty(char difficulty){
    tolower(difficulty);
    move(1,NBCOLUMNS+60);
    switch(difficulty){
        case 't':
            printw("Difficulté : Très Facile");
            break;
        case 'f':
            printw("Difficulté : Facile");
            break;
        case 'n':
            printw("Difficulté : Normale");
            break;
        case 'd':
            printw("Difficulté : Difficile");
            break;
    };

    return;
}

/*Affiche le menu du jeu*/
void menu_ui(char difficulty){
    erase();
    int key;
    draw_commands();
    move(19, NBCOLUMNS+15);
    printw("Jouer : J");
    draw_difficulty(difficulty);
    WINDOW *menuWindow = newwin(NBLINES,(NBCOLUMNS*2)+2,0,0);
    box(menuWindow, 0, 0);
    wmove(menuWindow,10,8);
    wprintw(menuWindow,"TETROS");
    wrefresh(menuWindow);
    timeout(0.1);  // Temporisation du getch
    while(key != 'j' && key != 'J'){
        if (key == 'q' || key == 'Q'){
            endwin();
            exit(0);
        }
        key = getch();
    }
    endwin();

    return;
}

void select_difficulty_ui(char* res){
    char key;
    initUI();
    WINDOW *select_difficulty_Window = newwin(NBLINES,(NBCOLUMNS*2)+2,0,0);
    wprintw(select_difficulty_Window,"Difficulté : \n\n Très Facile -> T\n\n Facile -> F\n\n Normale -> N\n\n Difficile -> D");
    wrefresh(select_difficulty_Window);
    while(key!='t' && key!='f' && key!='n' && key!='d' && key!='T' && key!='F' && key!='N' && key!='D' ){
        if (key == 'q' || key == 'Q'){
            endwin();
            exit(0);
        }
        key=getchar();
    }
    endwin();
    *res=key;
    return;

}

void end_ui(bool* gameOn,bool* inGame){
    erase();
    char key;
    initUI();
    WINDOW *end_Window = newwin(NBLINES,(NBCOLUMNS*2)+2,0,0);
    wprintw(end_Window,"La partie est finie !\n\nRejouer : J\n\nQuitter : Q");
    wrefresh(end_Window);
    while(key!='j' && key!='J' && key!='q' && key!='Q'){
        key=getchar();
    }
    if (key=='q' || key=='Q'){
        *gameOn=false;
    }
    else if(key=='j' || key=='J'){
        *inGame=true;
    }
    endwin();
    return;

}

/* Affiche le titre du jeu. Outil utilisé : textkool.com */
void drawTitle(){
    printf("\n");
    printf( "      _____                    _____                _____                    _____                   _______                   _____          \n"
            "     /\\    \\                  /\\    \\              /\\    \\                  /\\    \\                 /::\\    \\                 /\\    \\         \n"
            "    /::\\    \\                /::\\    \\            /::\\    \\                /::\\    \\               /::::\\    \\               /::\\    \\        \n"
            "    \\:::\\    \\              /::::\\    \\           \\:::\\    \\              /::::\\    \\             /::::::\\    \\             /::::\\    \\       \n"
            "     \\:::\\    \\            /::::::\\    \\           \\:::\\    \\            /::::::\\    \\           /::::::::\\    \\           /::::::\\    \\      \n"
            "      \\:::\\    \\          /:::/\\:::\\    \\           \\:::\\    \\          /:::/\\:::\\    \\         /:::/~~\\:::\\    \\         /:::/\\:::\\    \\   \n"  
            "       \\:::\\    \\        /:::/__\\:::\\    \\           \\:::\\    \\        /:::/__\\:::\\    \\       /:::/    \\:::\\    \\       /:::/__\\:::\\    \\    \n"
            "       /::::\\    \\      /::::\\   \\:::\\    \\          /::::\\    \\      /::::\\   \\:::\\    \\     /:::/    / \\:::\\    \\      \\:::\\   \\:::\\    \\   \n"
            "      /::::::\\    \\    /::::::\\   \\:::\\    \\        /::::::\\    \\    /::::::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\   ___\\:::\\   \\:::\\    \\  \n"
            "     /:::/\\:::\\    \\  /:::/\\:::\\   \\:::\\    \\      /:::/\\:::\\    \\  /:::/\\:::\\   \\:::\\____\\ |:::|    |     |:::|    | /\\   \\:::\\   \\:::\\    \\ \n"
            "    /:::/  \\:::\\____\\/:::/__\\:::\\   \\:::\\____\\    /:::/  \\:::\\____\\/:::/  \\:::\\   \\:::|    ||:::|____|     |:::|    |/::\\   \\:::\\   \\:::\\____\\\n"
            "   /:::/    \\::/    /\\:::\\   \\:::\\   \\::/    /   /:::/    \\::/    /\\::/   |::::\\  /:::|____| \\:::\\    \\   /:::/    / \\:::\\   \\:::\\   \\::/    /\n"
            "  /:::/    / \\/____/  \\:::\\   \\:::\\   \\/____/   /:::/    / \\/____/  \\/____|:::::\\/:::/    /   \\:::\\    \\ /:::/    /   \\:::\\   \\:::\\   \\/____/ \n"
            " /:::/    /            \\:::\\   \\:::\\    \\      /:::/    /                 |:::::::::/    /     \\:::\\    /:::/    /     \\:::\\   \\:::\\    \\     \n"
            "/:::/    /              \\:::\\   \\:::\\____\\    /:::/    /                  |::|\\::::/    /       \\:::\\__/:::/    /       \\:::\\   \\:::\\____\\    \n"
            "\\::/    /                \\:::\\   \\::/    /    \\::/    /                   |::| \\::/____/         \\::::::::/    /         \\:::\\  /:::/    /    \n"
            " \\/____/                  \\:::\\   \\/____/      \\/____/                    |::|  ~|                \\::::::/    /           \\:::\\/:::/    /     \n"
            "                           \\:::\\    \\                                     |::|   |                 \\::::/    /             \\::::::/    /      \n"
            "                            \\:::\\____\\                                    \\::|   |                  \\::/____/               \\::::/    /       \n"
            "                             \\::/    /                                     \\:|   |                   ~~                      \\::/    /        \n"
            "                              \\/____/                                       \\|___|                                            \\/____/         \n"
            "                                                                                                                                              \n\n" );
} 
