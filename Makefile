tetris: regles.o interface.o functions.o tetris.o
	gcc regles.o interface.o functions.o tetris.o -o tetris -lncurses

regles.o: regles.c
	gcc -c regles.c

interface.o: interface.c
	gcc -c interface.c

fucntions.o: fucntions.c
	gcc -c functions.c

tetris.o: tetris.c
	gcc -c tetris.c

clean:
	rm -f *.o
	rm -f tetris
