#include <stdbool.h>
#include <ncurses.h>

#include "header/mainMenu.h"
#include "header/mainGame.h"
#include "header/animation.h"

int main(){
	
	bool gameOn = true;
	
	initNcurses();
	int difficulty = -1;
	curs_set(0);  // Cache le curseur
	startAnimation();

	int key;

	int selection = 0;
	

	int score = 0;
	int highScore = 0;

	int gameMode = -1;
	// si gameMode est égal à 0, l'accélération de la descente des blocs sera proportionnelle au temps passé au cours d'une partie donnée
	// si gameMode est égal à 1, celle-ci sera proportionnelle au nombre de points déjà obtenus par le joueur
	while(gameOn){

		drawMenu(selection, highScore);
		
		key = getch();

		/* Déplacement du bouton sélectionné dans l'interface. */
		switch(key){

			case 'q' :	// Touche Q
			gameOn = false;
			exitAnimation();
			break;

			case 65 :	// Flèche Haut
			if(selection > 0) selection--;
			break;

			case 66 :	// Flèche Bas
			if(selection < 5) selection++;
			break;

			case 10:	// Touche Entrée
	        switch(selection){

				case 0 : // Sélection du mode de jeu
				gameModePicker(&gameMode);
				break;

				case 1 :
				difficultyPicker(&difficulty);
				break;
	            
	            case 2 :	// Jouer
	            if (difficulty != -1 && gameMode!=-1){
					clear();
	            	score = 0;
	            	playTetros(difficulty, &score, gameMode);
					clear();
	            	if (score > highScore) highScore = score;  // Enregistrement du score si meilleur.
	            }
				else{
					drawDiffNotSet(difficulty,gameMode);
				}
	            break;

	            
	            case 3 :	// Aide
	            drawHelp();
	            break;

	            case 4 :	// Crédits
	            drawCredits();
	            break;

	            case 5 :	//Quitter
	            gameOn = false;
	            exitAnimation();
	            break;

	        }
			break;

		};
	}
	endwin();
	return 0;
}