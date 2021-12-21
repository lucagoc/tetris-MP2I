#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include "interface.h"
#include "regles.h"
#include "debug.h"



int main(){
    int res;
    int time;
    int timeCycle;
    printf("Veuillez choisir un niveau de difficulté en entrant une valeur comprise entre 1 et 4 : ");
    scanf("%d",&res);
    if(res==1 || res==2 || res==3 || res==4){
        time = 0;
        timeCycle = set_difficulty(res);
    }
    else{
        printf("Saisie incorrecte, merci d'entrer une valeur comprise entre 1 et 4.\n");
        exit(0);
    }


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
    drawUI(mainGrid, mobileGrid, inventory, gridWindow);

    int tetriminoID = genTetrimino(mobileGrid, setRandom(0));
    int priorID = tetriminoID; //Utile pour les comparaisons.

    /*Commande de controle*/
    int key;
    bool inGame = true;
    while(inGame == true){
        while(time < timeCycle){
            timeout(1);
            key = getch();
            switch(key){
                case 65: //flèche haut
                    goBottom(mainGrid, mobileGrid);
                    tetriminoID = putTetrimino(mainGrid, mobileGrid, tetriminoID);
                    printLogkey(fp, '^');
                    break;
                case 66: //Touche flèche bas
                    tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID);
                    printLogkey(fp, 'B');
                    time--; // Evite une accélération trop rapide du tétrimino lors de sa chute.
                    break;
                case 67: //Touche flèche droite
                    goRight(mainGrid, mobileGrid);
                    printLogkey(fp, '>');
                    break;
                case 68: //Touche flèche gauche
                    goLeft(mainGrid, mobileGrid);
                    printLogkey(fp, '<');
                    break;
                case 'q': //Touche Q pour quitter la boucle.
                    inGame = false;
                    break;
                case 'd': //Rotation
                    turnTetrimino(mainGrid, mobileGrid);
                    printLogkey(fp, 'd');
                    time--;
                    break;
                case 'y': //Génére un bloc de debug
                    genDebugtetrimino(mobileGrid);
                    printLogkey(fp, 'y');
                    tetriminoID = BLOCK_DEBUG;
                    break;
                case 's': //Réserve
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
                    break;
                case 'p': //Pause
                    pause();
                    printLogkey(fp, 'p');
                    break;
            };

            //Réactive l'accès à l'inventaire si le tetrimino a changé
            if(tetriminoID != priorID) invUsed = false;

            drawUI(mainGrid, mobileGrid, inventory, gridWindow);
            time++;
        }

        tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID);
        time = 0;
    }

    endwin();
    return 0;
}
