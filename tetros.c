#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "tetrimino.h"
#include "interface.h"
#include "regles.h"
#include "debug.h"


int main(){
    char temp;
    drawTitle();
    printf("Bienvenue sur TETROS! Si vous souhaitez jouer, entrez J, sinon entrez une autre touche : ");
    scanf("%c",&temp);
    if(temp!='j' && temp!='J'){
        exit(0);
    }
    else{
        bool gameOn=true;
        while (gameOn){
            char res;
            int res2;
            int time;
            int timeCycle;
            int timeOut;
            int points_per_line;
            int score = 0;
            int score_counter = 0;
            int score_counter_before = 0;
            curs_set(0);
            refresh();
        
            select_difficulty_ui(&res);
            time = 0;
            timeCycle = set_difficulty(&res);
            timeOut = set_delay(&res);
            points_per_line=set_points_per_line(&res);

            menu_ui(res);

            FILE *fp = initLogfile(); //

            int mainGrid[NBLINES][NBCOLUMNS];
            int mobileGrid[NBLINES][NBCOLUMNS];
            int inventory = 0;
            bool invUsed = false;

            initGrid(mainGrid);
            initGrid(mobileGrid);

            initUI();
            WINDOW *gridWindow = newwin(NBLINES,(NBCOLUMNS*2)+2,0,0);  // Création de la fenêtre de jeu
            bool inGame=true;
            drawUI(mainGrid, mobileGrid, inventory, gridWindow,&inGame,&score_counter);

            int tetriminoID = genTetrimino(mobileGrid, setRandom(0));
            int priorID = tetriminoID;  // Correspond à l'ID du tetrimino précédent.

            draw_score(&score, score_counter, points_per_line);
            /*Commandes de contrôle*/
            int key;
            while(inGame){
                while(time < timeCycle){
                    timeout(1);

                    key = getch();
                    if(key == 65){  // Flèche haut
                        printLogkey(fp, '^');
                        goBottom(mainGrid, mobileGrid,&inGame,&score_counter);
                        drawUI(mainGrid, mobileGrid, inventory, gridWindow,&inGame,&score_counter); //refresh pour l'animation.
                        tetriminoID = putTetrimino(mainGrid, mobileGrid, tetriminoID, 0,&inGame,&score_counter);
                    }
                    else if(key == 66){  // Flèche bas
                        printLogkey(fp, 'B');
                        tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut,&inGame,&score_counter);
                        time--;  // Evite une accélération trop rapide du tétrimino lors de sa chute.
                    }
                    else if(key == 67){  // Flèche droite
                        printLogkey(fp, '>');
                        goRight(mainGrid, mobileGrid);
                    }
                    else if(key == 68){  // Flèche gauche
                        printLogkey(fp, '<');
                        goLeft(mainGrid, mobileGrid);
                    }
                    else if(key == 'q' || key == 'Q'){
                        printLogkey(fp, 'q');
                        inGame = false;
                    }
                    else if(key == 'd' || key == 'D'){
                        printLogkey(fp, 'd');
                        turnTetrimino(mainGrid, mobileGrid);
                        time--;
                    }
                    else if(key =='y' || key == 'Y'){
                        printLogkey(fp, 'y');
                        if (DEBUG_MODE==true){
                            genDebugtetrimino(mobileGrid);
                            tetriminoID = BLOCK_DEBUG;
                        }
                    }
                    else if(key == 's' || key == 'S'){
                        printLogkey(fp, 's');
                        if(invUsed == false){
                            if(inventory == 0){ // Cas où il n'y a pas encore de bloc dans l'inventaire.
                                initGrid(mobileGrid);
                                inventory = tetriminoID;
                                tetriminoID = genTetrimino(mobileGrid, setRandom(tetriminoID));
                                priorID = tetriminoID;
                            } else { // Cas normal
                                int temp = tetriminoID;
                                initGrid(mobileGrid);
                                tetriminoID = genTetrimino(mobileGrid, inventory);
                                priorID = tetriminoID;
                                inventory = temp;
                            }
                            invUsed = true;
                        }
                    }
                    else if(key == 'p' || key == 'P'){
                        printLogkey(fp, 'p');
                        pause();
                    }

                    if(tetriminoID != priorID) invUsed = false;  // Redonne l'accès à l'inventaire si le tetrimino a changé

                    drawUI(mainGrid, mobileGrid, inventory, gridWindow, &inGame, &score_counter);

                    if (score_counter != score_counter_before){
                        draw_score(&score, score_counter, points_per_line);
                        score_counter_before = score_counter;
                    }

                    time++;
                }
                
                tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut,&inGame,&score_counter);
                time = 0;
            }

            endwin();
            end_ui(&gameOn,&inGame);
            }
        }
    return 0;

}
