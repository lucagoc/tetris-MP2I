#include <stdbool.h>
#include <ncurses.h>
#include <time.h>

#include "header/rules.h"
#include "header/tetrimino.h"
#include "header/gameUI.h"
#include "header/debug.h"


void playTetros(int difficulty, int* score, int gameMode){

	int key;
	int tetriminoID;
	bool tetriminoPlaced;
	int temp_score = 0;

    /* Timer */
	int timeCounting = 0;
    time_t timeStarted = time(NULL);

	int time_gm1 = 0;

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
    initGrid(mobileGrid);  // On initialise les 2 grilles en les remplissant de 0

    /* Boucle principal du jeu */
	bool inGame = true;
	while(inGame){

		if((int)timer(timeStarted) >= time_gm1+10 && gameMode == 0 && speedCycle>50){
			speedCycle = speedCycle-15;
			time_gm1 = timer(timeStarted);
			if (speedCycle < 50) speedCycle = 50;
		}
		/* 	Si le mode de jeu sélectionné est celui dépendant du temps, on stocke dans time_gm1 la valeur de timer(timeStarted) qui correspond au nombre de secondes écoulées depuis le lancement du jeu
		 *	Ensuite, toutes les 10 secondes, on décrémente speedCycle pour accélérer la descente des blocs, on affecte à time_gm1 la temps écoulé depuis le début de la partie
		 *	On répète ceci jusqu'à que speedCycle soit inférieur à 50, cette vitesse rendant déjà le jeu très difficile, on fixe speedCycle à 50 jusqu'à la fin de la partie
		 */

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
						if(DEBUG_MODE == true){
                			genDebugtetrimino(mobileGrid);
						}
                		break;

                	case 's':	// Touche S
                		if (invUsed == false) switchInventory(mainGrid, mobileGrid, &tetriminoID, &inventory);
                		invUsed = true;
                		break;

                	case 'p':	// Touche P
                		pause(&timeStarted);
                		break;
                };

                /* Actualisation de l'écran */
                drawGame(mainGrid, mobileGrid, inventory, *score, timer(timeStarted), difficulty, gridWindow, gameMode);
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

		if (gameMode == 1 && *score > temp_score && speedCycle > 50){
			speedCycle = speedCycle - (((*score) - (temp_score)) / 10);
			if (speedCycle < 50) speedCycle = 50;
			temp_score = *score;
		}
		/* 	Si le mode de jeu sélectionné est celui dépendant des points, on stocke dans temp_score la valeur de score qui correspond au nombre de points accumulés par le joueur
		 *	Ensuite, à chaque placement de tetrimino, on vérifie si le joueur a gagné des points en comparant la valeur de score avec temp_score, si c'est le cas on décrémente speedCycle 
		 *	pour accélérer la descente des blocs en fonction du nombre de points gagnés par rapport au score précédent
		 *	On affecte ensuite à temp_score la valeur actuelle de score 
		 *	On répète ceci jusqu'à que speedCycle soit inférieur à 50, cette vitesse rendant déjà le jeu très difficile, on fixe speedCycle à 50 jusqu'à la fin de la partie
		 */

        /* Fin du jeu */
        if (isGridfull(mainGrid)){
          	inGame = false;
        }

        invUsed = false;
	}

	return;
}

