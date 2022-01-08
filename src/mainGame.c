#include <stdbool.h>
#include <ncurses.h>
#include <time.h>

#include "header/rules.h"
#include "header/tetrimino.h"
#include "header/gameUI.h"


void playTetros(int difficulty, int* score){

	int key;
	int tetriminoID;
	bool tetriminoPlaced;

    /* Timer */
	int timeCounting = 0;
    time_t timeStarted = time(NULL);

    /* Difficulté */
	int speedCycle;
    setDifficulty(difficulty, &speedCycle);

    /* Inventaire */
	int inventory = 0; // Bloc vide
	bool invUsed = false;

    /* Grille*/
	int mainGrid[NBLINES][NBCOLUMNS];
    int mobileGrid[NBLINES][NBCOLUMNS];
    initGrid(mainGrid);
    initGrid(mobileGrid);

    /* Boucle principal du jeu */
	bool inGame = true;
	while(inGame){

        /* Fenêtre du jeu */
        WINDOW *gridWindow = newwin(NBLINES,(NBCOLUMNS*2)+2,1,3);

        /* Génération d'un tetrimino*/
		setRandom(&tetriminoID);
		genTetrimino(mobileGrid, tetriminoID);

        /* Boucle d'un tetrimino */
		tetriminoPlaced = false;
		while(tetriminoPlaced == false){
			while(timeCounting < speedCycle){
                
                timeout(1);
                key = getch();

                /* Commande de contrôle */
                switch(key){

                	case 65:	// Flèche Haut
                		goBottom(mainGrid, mobileGrid);
                		tetriminoPlaced = true;
                		timeCounting = speedCycle;
                		break;

                	case 66:	// Flèche Bas
                		if(isDownfree(mainGrid, mobileGrid)) goDown(mainGrid, mobileGrid);
                		else {
                            tetriminoPlaced = true;
                            timeCounting = speedCycle;
                        }
                		break;

                	case 67:	// Flèche Droite
                		goRight(mainGrid, mobileGrid);
                        if(isDownfree(mainGrid, mobileGrid) == false) timeCounting = 0;
                		break;

                	case 68:	// Flèche Gauche
                		goLeft(mainGrid, mobileGrid);
                        if(isDownfree(mainGrid, mobileGrid) == false) timeCounting = 0;
                		break;

                	case 'q':	// Touche Q
                		timeCounting = speedCycle;
                		tetriminoPlaced = true;
                		inGame = false;
                		break;

                	case 'd':	// Touche D
                		turnTetrimino(mainGrid, mobileGrid);
                		timeCounting = 0;
                		break;

                	case 'y':	// Touche Y
                		// genDebugtetrimino(mobileGrid);
                		break;

                	case 's':	// Touche S
                		if (invUsed == false) switchInventory(mainGrid, mobileGrid, &tetriminoID, &inventory);
                		invUsed = true;
                		break;

                	case 'p':	// Touche P
                		pause();
                		break;
                };

                /* Actualisation de l'écran */
                drawGame(mainGrid, mobileGrid, inventory, *score, timer(timeStarted), difficulty, gridWindow);
                timeCounting++;
            }

            /* Descente du tetrimino */
            if(isDownfree(mainGrid, mobileGrid)) goDown(mainGrid, mobileGrid);
            else tetriminoPlaced = true;
            timeCounting = 0;
		}

		/* Placement du tetrimino */
		putTetrimino(mainGrid, mobileGrid);
		initGrid(mobileGrid);

        /* Scoring */
        int nbLinesfull = countLinesfull(mainGrid);
        scoring(nbLinesfull, difficulty, score);

        /* Fin du jeu */
        if (isGridfull(mainGrid)){
          	inGame = false;
        }

        invUsed = false;
	}

	return;
}

