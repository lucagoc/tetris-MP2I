tetris: regles.o interface.o functions.o tetris.o debug.o
	gcc regles.o interface.o functions.o tetris.o debug.o -o tetris -lncurses

regles.o: regles.c
	gcc -c regles.c

interface.o: interface.c
	gcc -c interface.c

functions.o: functions.c
	gcc -c functions.c

debug.o: debug.c
	gcc -c debug.c

tetris.o: tetris.c functions.h interface.h regles.h debug.h
	gcc -c tetris.c

clean:
	rm -f *.o
	rm -f tetris
