tetros: rules.o gameUI.o tetrimino.o debug.o mainGame.o mainMenu.o main.o
	gcc rules.o gameUI.o tetrimino.o debug.o mainGame.o mainMenu.o main.o -o tetros -lncurses

rules.o: src/rules.c
	gcc -c src/rules.c

gameUI.o: src/gameUI.c
	gcc -c src/gameUI.c

tetrimino.o: src/tetrimino.c
	gcc -c src/tetrimino.c

debug.o: src/debug.c
	gcc -c src/debug.c

mainGame.o : src/mainGame.c
	gcc -c src/mainGame.c

mainMenu.o : src/mainMenu.c
	gcc -c src/mainMenu.c

main.o: src/main.c src/header/mainGame.h src/header/tetrimino.h src/header/rules.h src/header/debug.h src/header/mainMenu.h src/header/gameUI.h
	gcc -c src/main.c

clean:
	rm -f *.o
	rm -f tetros