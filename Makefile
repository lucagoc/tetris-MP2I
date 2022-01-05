tetros: regles.o interface.o tetrimino.o tetros.o debug.o
	gcc regles.o interface.o tetrimino.o tetros.o debug.o -o tetros -lncurses

regles.o: regles.c
	gcc -c regles.c

interface.o: interface.c
	gcc -c interface.c

tetrimino.o: tetrimino.c
	gcc -c tetrimino.c

debug.o: debug.c
	gcc -c debug.c

tetros.o: tetros.c tetrimino.h interface.h regles.h debug.h
	gcc -c tetros.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f tetros