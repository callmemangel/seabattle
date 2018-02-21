all: sea

sea: main.o game.o ships.o machine.o
	gcc main.o game.o ships.o machine.o -o sea

main.o: main.c
	gcc -c main.c

game.o: game.c
	gcc -c game.c

ships.o: ships.c
	gcc -c ships.c

machine.o: machine.c
	gcc -c machine.c

clean: 
	rm -rf *.o 
