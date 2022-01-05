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

    bool gameOn = true;

    while (gameOn){

        int key;
        int time;
        int timeCycle;
        int timeOut;
        int points_per_line;
        int score = 0;
        int score_counter = 0;
        int score_counter_before = 0;
        
        /*Ecran titre*/
        drawTitle();
        printf("Veuillez choisir un niveau de difficulté en entrant une valeur comprise entre 1 et 4 : ");
        scanf("%d", &key);
        if (key == 1 || key == 2 || key == 3 || key == 4){
            time = 0;
            timeCycle = set_difficulty(key);
            timeOut = set_delay(key);
            points_per_line = set_points_per_line(key);
        } else {
            printf("Saisie incorrecte, merci d'entrer une valeur comprise entre 1 et 4.\n");
            exit(0);
        }

        /* Affichage du menu de jeu */
        menu_ui();

        /* LogFile */
        FILE *fp = initLogfile();

        /* Création des grilles de jeu. */
        int mainGrid[NBLINES][NBCOLUMNS];
        int mobileGrid[NBLINES][NBCOLUMNS];

        /* Initialisation des paramètres du jeu */
        initGrid(mainGrid);
        initGrid(mobileGrid);
        int tetriminoID = genTetrimino(mobileGrid, setRandom(0));
        int priorID = tetriminoID;  // Correspond à l'ID du tetrimino précédent.
        int inventory = 0;
        bool invUsed = false;
        bool inGame = true;

        /*Affichage de l'interface*/
        initUI();
        WINDOW *gridWindow = newwin(NBLINES, (NBCOLUMNS*2)+2, 0, 0);  // Fenêtre de jeu
        drawUI(mainGrid, mobileGrid, inventory, gridWindow, &inGame, &score_counter);
        draw_score(&score, score_counter, points_per_line);

        /*Boucle principale du jeu*/
        while(inGame){
            while(time < timeCycle){

                timeout(1);
                key = getch();

                /*Commandes de contrôle*/
                if (key == 65){                             // Flèche haut
                    printLogkey(fp, '^');
                    goBottom(mainGrid, mobileGrid, &inGame, &score_counter);
                    drawUI(mainGrid, mobileGrid, inventory, gridWindow, &inGame, &score_counter); //refresh pour l'animation.
                    tetriminoID = putTetrimino(mainGrid, mobileGrid, tetriminoID, 0, &inGame, &score_counter);

                } else if (key == 66){                        // Flèche bas
                    printLogkey(fp, 'B');
                    tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut, &inGame, &score_counter);
                    time--;  // Evite une accélération trop rapide du tétrimino lors de sa chute.

                } else if (key == 67){                        // Flèche droite
                    printLogkey(fp, '>');
                    goRight(mainGrid, mobileGrid);

                } else if (key == 68){                        // Flèche gauche
                    printLogkey(fp, '<');
                    goLeft(mainGrid, mobileGrid);

                } else if (key == 'q' || key == 'Q'){         // Touche Q
                    printLogkey(fp, 'q');
                    inGame = false;

                } else if (key == 'd' || key == 'D'){         // Touche D
                    printLogkey(fp, 'd');
                    turnTetrimino(mainGrid, mobileGrid);
                    time--;

                } else if (key == 'y' || key == 'Y'){         // Touche Y
                    printLogkey(fp, 'y');
                    if (DEBUG_MODE){
                        genDebugtetrimino(mobileGrid);
                        tetriminoID = BLOCK_DEBUG;
                    }

                } else if (key == 's' || key == 'S'){         // Touche S
                    printLogkey(fp, 's');
                    if (invUsed == false){
                        if (inventory == 0){ // Cas où il n'y a pas encore de bloc dans l'inventaire.
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

                } else if (key == 'p' || key == 'P'){         // Touche P
                    printLogkey(fp, 'p');
                    pause();
                }

                if (tetriminoID != priorID) invUsed = false;  // Redonne l'accès à l'inventaire si le tetrimino a changé

                drawUI(mainGrid, mobileGrid, inventory, gridWindow, &inGame, &score_counter);
                if (score_counter != score_counter_before){
                    draw_score(&score, score_counter, points_per_line);
                    score_counter_before = score_counter;
                }

                time++;
            }
            
            tetriminoID = goDown(mainGrid, mobileGrid, tetriminoID, timeOut, &inGame, &score_counter);
            time = 0;
        }

        /* Fin de partie */
        endwin();
        printf("Fin de partie, vous avez fait un score de %d \n", score);
        printf("Voulez-vous rejouer ? Entrez 1 pour rejouer, sinon entrez 0.\n");
        scanf("%d", &key);
        if (key == 1){
            inGame = true;
        } else if (key == 0){
            gameOn = false;
        } else {
            printf("Saisie incorrecte, merci de saisir 1 ou 0 uniquement. Sortie... \n");
            gameOn = false;
        }
    }

    return 0;
}
