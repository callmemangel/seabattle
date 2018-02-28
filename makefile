all: sea

sea: main.o game.o ships.o machine.o window.o cursor.o stack.o getch.o
	gcc main.o game.o ships.o machine.o window.o cursor.o stack.o getch.o -lm -o sea

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

cursor.o: cursor.c
	gcc -c cursor.c

stack.o: stack.c
	gcc -c stack.c

getch.o: getch.c
	gcc -c getch.c

clean: 
	rm -rf *.o 
