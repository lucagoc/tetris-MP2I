#include <stdbool.h>
#include <ncurses.h>

#include "header/mainMenu.h"
#include "header/mainGame.h"
#include "header/animation.h"

int main(){
	
	bool gameOn = true;
	
	initNcurses();
	curs_set(0);  // Cache le curseur
	startAnimation();

	int key;
	int selection = 0;

	int score = 0;
	int highScore = 0;

	int difficulty = -1;
	int gameMode = -1;
	/* 
	 * gameMode = 0, l'accélération de la descente des blocs sera proportionnelle au temps passé au cours d'une partie donnée
	 * gameMode = 1, celle-ci sera proportionnelle au nombre de points déjà obtenus par le joueur
	 */

	while(gameOn){

		drawMenu(selection, highScore); // Affichage du menu du jeu
		
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
			if(selection < 3) selection++;
			break;

			case 10:	// Touche Entrée
	        switch(selection){
	            
	            case 0 :	// Jouer
	            gameModePicker(&gameMode);
	            if (gameMode != -1){
	            	difficultyPicker(&difficulty);
	            	if (difficulty != -1){
						clear();
		            	score = 0;
		            	playTetros(difficulty, &score, gameMode);
						clear();
		            	if (score > highScore) highScore = score;  // Enregistrement du score si meilleur.
		            }
	        	}
	        	gameMode = -1;
	        	difficulty = -1;
	            break;
	            
	            case 1 :	// Aide
	            drawHelp();
	            break;

	            case 2 :	// Crédits
	            drawCredits();
	            break;

	            case 3 :	//Quitter
	            gameOn = false;
	            exitAnimation();
	            break;

	        }
			break;

		};
	}
	endwin(); // Fin de l'affichage ncurses
	return 0;
}