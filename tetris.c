#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "functions.h"
#include "interface.h"
#include "regles.h"
#include "debug.h"


int main(){
    bool gameOn=true;
    while (gameOn){
        int res;
        int time;
        int timeCycle;
        int timeOut;
        int points_per_line;
        int score = 0;
        int score_counter = 0;
        int score_counter_before = 0;
 
        drawTitle();
        printf("Veuillez choisir un niveau de difficulté en entrant une valeur comprise entre 1 et 4 : ");
        scanf("%d",&res);
        if(res==1 || res==2 || res==3 || res==4){
            time = 0;
            timeCycle = set_difficulty(res);
            timeOut = set_delay(res);
            points_per_line=set_points_per_line(res);
        }
        else{
            printf("Saisie incorrecte, merci d'entrer une valeur comprise entre 1 et 4.\n");
            exit(0);
        }

        menu_ui();
        curs_set(2);



        /*Ecrit un fichier de debug si le debug mode est activé, voir regles.c*/
        FILE *fp = initLogfile();

        int mainGrid[NBLINES][NBCOLUMNS];
        int mobileGrid[NBLINES][NBCOLUMNS];
        int inventory = 0; //inventaire vide
        bool invUsed = false; // Permet de savoir si l'inventaire a été utilisé.

        initGrid(mainGrid);
        initGrid(mobileGrid);


        initUI();
        WINDOW *gridWindow = newwin(NBLINES,(NBCOLUMNS*2)+2,0,0); //création de la fenêtre de jeu, nombre de colonnes multiplié par 2 pour faire des carrés.
        bool inGame=true;
        drawUI(mainGrid, mobileGrid, inventory, gridWindow,&inGame,&score_counter);

        int tetriminoID = genTetrimino(mobileGrid, setRandom(0));
        int priorID = tetriminoID; //Utile pour les comparaisons.

        draw_score(&score,score_counter,points_per_line);

        /*Commande de controle*/
        int key;
        while(inGame){
            while(time < timeCycle){
                timeout(1);
                key = getch();

                if(key==65){
                    goBottom(mainGrid, mobileGrid,&inGame,&score_counter);
                    drawUI(mainGrid, mobileGrid, inventory, gridWindow,&inGame,&score_counter); //refresh pour l'animation.
                    tetriminoID = putTetrimino(mainGrid, mobileGrid, tetriminoID, 0,&inGame,&score_counter);
                    printLogkey(fp, '^');
                }
                else if(key==66){
                    tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut,&inGame,&score_counter);
                    printLogkey(fp, 'B');
                    time--; // Evite une accélération trop rapide du tétrimino lors de sa chute.
                }
                else if(key==67){
                    goRight(mainGrid, mobileGrid);
                    printLogkey(fp, '>');
                }
                else if(key==68){
                    goLeft(mainGrid, mobileGrid);
                    printLogkey(fp, '<');
                }
                else if(key=='q' || key=='Q'){
                    inGame=false;
                }
                else if(key=='d' || key=='D'){
                    turnTetrimino(mainGrid, mobileGrid);
                    printLogkey(fp, 'd');
                    time--;
                }
                else if(key =='y' || key=='Y'){
                    if (DEBUG_MODE==true){
                        genDebugtetrimino(mobileGrid);
                        printLogkey(fp, 'y');
                        tetriminoID = BLOCK_DEBUG;
                    }
                }
                else if(key=='s' || key=='S'){
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
                    printLogkey(fp, 's');
                }
                else if(key=='p' || key=='P'){
                    pause();
                    printLogkey(fp, 'p');
                }

                //Réactive l'accès à l'inventaire si le tetrimino a changé
                if(tetriminoID != priorID) invUsed = false;
                drawUI(mainGrid, mobileGrid, inventory, gridWindow,&inGame,&score_counter);
                if (score_counter!=score_counter_before){
                    draw_score(&score,score_counter,points_per_line);
                    score_counter_before=score_counter;
                }
                time++;
                
            }
            
            tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut,&inGame,&score_counter);
            time = 0;
        }
    endwin();
    printf("Fin de partie\n");
    int res2;
    printf("Voulez-vous rejouer ? Entrez 1 pour rejouer, sinon entrez 0.\n");
    scanf("%d",&res2);
    if(res2 == 1){
        inGame = true;

    }
    else if(res2 == 0){
        gameOn = false;
    }else{
        printf("Saisie incorrecte, merci de saisir 1 ou 0 uniquement.\n");
        gameOn = false;
    }

    }

    return 0;
}
