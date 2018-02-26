all: sea

sea: main.o game.o ships.o machine.o window.o 
	gcc main.o game.o ships.o machine.o window.o -lm -o sea

main.o: main.c
	gcc -c main.c

game.o: game.c
	gcc -c game.c

ships.o: ships.c
	gcc -c ships.c

machine.o: machine.c
	gcc -c machine.c

window.o: window.c
	gcc -c window.c

clean: 
	rm -rf *.o 
