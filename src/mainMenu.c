#include <ncurses.h>

#include "header/tetrimino.h"
#include "header/animation.h"

/* Initialise le module Ncurses */
void initNcurses(){

	initscr();
    start_color();

    /*Création des palettes de couleurs*/
    init_pair(BLOCK_O, COLOR_BLACK, COLOR_YELLOW);
    init_pair(BLOCK_I, COLOR_BLACK, COLOR_CYAN);
    init_pair(BLOCK_S, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLOCK_Z, COLOR_BLACK, COLOR_RED);
    init_pair(BLOCK_L, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLOCK_J, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLOCK_T, COLOR_BLACK, COLOR_MAGENTA);

    noecho();  // Cache les touches pressées
    refresh();

    return;
}

/* Affiche la fenêtre des difficultés */
void drawDifficultyPicker(int selection){
    WINDOW *difficultyWindow = newwin(12, 21, 15, 80);
    box(difficultyWindow, 0, 0);
    wmove(difficultyWindow, 1, 2);
    if(selection == 0) wprintw(difficultyWindow, "-> ");
    wprintw(difficultyWindow, "Très Facile");
    wmove(difficultyWindow, 3, 2);
    if(selection == 1) wprintw(difficultyWindow, "-> ");
    wprintw(difficultyWindow, "Facile");
    wmove(difficultyWindow, 5, 2);
    if(selection == 2) wprintw(difficultyWindow, "-> ");
    wprintw(difficultyWindow, "Normal");
    wmove(difficultyWindow, 7, 2);
    if(selection == 3) wprintw(difficultyWindow, "-> ");
    wprintw(difficultyWindow, "Difficile");
    wmove(difficultyWindow, 10, 2);
    if(selection == 4) wprintw(difficultyWindow, "-> ");
    wprintw(difficultyWindow, "Retour");
    
    wrefresh(difficultyWindow);
}

/* Affiche le menu de sélection de la difficulté */

void difficultyPicker(int* difficulty){

    int key;
    int selection = 0;

    bool menuOpen = true;
    while(menuOpen){
        drawDifficultyPicker(selection);
        key = getch();

        switch(key){

            case 'q' :  // Touche Q
            *difficulty = -1;
            menuOpen = false;
            break;

            case 65 :   // Flèche Haut
            if(selection > 0) selection--;
            break;

            case 66 :   // Flèche Bas
            if(selection < 4) selection++;
            break;

            case 10:    // Touche Entrée
            switch(selection){
                
                case 0 :    // Très Facile
                *difficulty = 0;
                menuOpen = false;
                break;
                
                case 1 :    // Normal
                *difficulty = 1;
                menuOpen = false;
                break;

                case 2 :    // Difficile
                *difficulty = 2;
                menuOpen = false;
                break;

                case 3 :    // Très Difficile
                *difficulty = 3;
                menuOpen = false;
                break;

                case 4 :    // Retour
                *difficulty = -1;
                menuOpen = false;
                break;

            };
            break;

        };

    }

    return;
}

/* Affiche la fenêtre des modes de jeu */

void drawGameModePicker(int selection){
    WINDOW *gameModeWindow = newwin(12, 66, 15, 13);
    box(gameModeWindow, 0, 0);
    wmove(gameModeWindow, 1, 2);
    wprintw(gameModeWindow,"L'accélération de la descente des blocs au cours de la partie");
    wmove(gameModeWindow, 2, 2);
    wprintw(gameModeWindow,"dépendra du paramètre sélectionné ci-dessous : ");

    wmove(gameModeWindow, 4, 2);
    if(selection == 0) wprintw(gameModeWindow, "-> ");
    wprintw(gameModeWindow, "Temps écoulé");
    wmove(gameModeWindow, 6, 2);
    if(selection == 1) wprintw(gameModeWindow, "-> ");
    wprintw(gameModeWindow, "Nombre de points");
    wmove(gameModeWindow, 10, 2);
    if(selection == 2) wprintw(gameModeWindow, "-> ");
    wprintw(gameModeWindow, "Retour");
    wrefresh(gameModeWindow);
    return;
}

/* Affiche le menu de sélection du mode de jeu */

void gameModePicker(int* gameMode){
    int key;
    int selection = 0;

    bool menuOpen = true;
    while(menuOpen){
        drawGameModePicker(selection);
        key = getch();

        switch(key){

            case 'q' :  // Touche Q
            menuOpen = false;
            break;

            case 65 :   // Flèche Haut
            if(selection > 0) selection--;
            break;

            case 66 :   // Flèche Bas
            if(selection < 2) selection++;
            break;

            case 10:    // Touche Entrée
            switch(selection){

                case 0 :
                *gameMode=0;
                menuOpen = false;
                break;

                case 1 :
                *gameMode = 1;
                menuOpen = false;
                break;

                case 2 :
                *gameMode = -1;
                menuOpen = false;
                break;
            };
            break;

        };

    }

    return;
}


/* Affiche les boutons de sélection sur le menu principal */
void drawButton(int selection){
    curs_set(0);
    move(17, 2);
    if(selection == 0) printw("-> ");
    printw("Jouer");
    move(19, 2);
    if(selection == 1) printw("-> ");
    printw("Aide");
    move(21, 2);
    if(selection == 2) printw("-> ");
    printw("Crédits");
    move(23, 2);
    if(selection == 3) printw("-> ");
    printw("Quitter");

    return;
}

/* Affiche le meilleur score sur le menu*/
void drawMenuscore(int highScore){
    move(28, 2);
    printw("Meilleur score : %d", highScore);

    return;
}

/* Affiche le menu principal */
void drawMenu(int selection, int highScore){

    erase();

    animatedTitle(13);
    drawButton(selection);
    drawMenuscore(highScore);

    refresh();

    return;
}

/* Affiche le menu d'aide */
void drawHelp(){

    WINDOW *helpWindow = newwin(8, 80, 17, 12);
    box(helpWindow, 0, 0);

    wmove(helpWindow, 1, 2);
    wprintw(helpWindow, "Si vous constatez un bug, veuillez nous contacter à l'adresse suivante : ");
    wmove(helpWindow, 3, 2);
    wprintw(helpWindow, "tetros_bcf@gmail.com");
    wmove(helpWindow, 6, 2);
    wprintw(helpWindow, "Appuyez sur une touche pour fermer...");
    wrefresh(helpWindow);

    timeout(-1);
    getch();

    return;
}

/* Affiche le menu des crédits */
void drawCredits(){

    WINDOW *creditsWindow = newwin(8 , 50, 18, 14);
    box(creditsWindow, 0, 0);
    wmove(creditsWindow, 1, 2);
    wprintw(creditsWindow, "TETROS PAR :");
    wmove(creditsWindow, 3, 2);
    wprintw(creditsWindow, "LUCAS BALMES  X  THEO COURT  X  ADRIEN FRACHET");

    wmove(creditsWindow, 6, 2);
    wprintw(creditsWindow, "Appuyez sur une touche pour fermer...");
    wrefresh(creditsWindow);

    timeout(-1);
    getch();


    return;
}
