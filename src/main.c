#include <stdbool.h>
#include <ncurses.h>

#include "header/mainMenu.h"
#include "header/mainGame.h"

int main(){
	
	bool gameOn = true;
	
	initNcurses();

	int key;
	int selection = 0;
	int difficulty = -1;

	int score = 0;
	int highScore = 0;

	while(gameOn){

		drawMenu(selection, highScore);
		
		key = getch();

		/* Déplacement du bouton sélectionner dans l'interface. */
		switch(key){

			case 'q' :	// Touche Q
			gameOn = false;
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
	            difficultyPicker(&difficulty);
	            if (difficulty != -1) {
	            	clear();
	            	score = 0;
	            	playTetros(difficulty, &score);
	            	if (score > highScore) highScore = score;  // Enregistrement du score si meilleur.
	            }
	            break;
	            
	            case 1 :	// Aide
	            drawHelp();
	            break;

	            case 2 :	// Crédit
	            drawCredits();
	            break;

	            case 3 :	//Quitter
	            gameOn = false;
	            break;

	        }
			break;

		};
	}
	endwin();
	return 0;
}