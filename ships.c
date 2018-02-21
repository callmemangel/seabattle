#include "machine.h"
#include "ships.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>



void setShips (Cell field[][SIZE], Ship* ships, char gameMode)
{
    int shipsToSet[] = {4, 3, 2, 1};

    char setMode = getSetMode(gameMode);

    int* coords;

    int currShip = 0;

    while (!isEmpty (shipsToSet)) {

        system("clear");
        showShipsToSet(shipsToSet);
        drawField(field);

        Ship ship = ships[currShip];

        coords = getCoords(setMode);   

        ship.id = currShip;
        ship.size = calcSize(coords);
        ship.isKilled = false;

        if(!contains(ship, shipsToSet))
            continue;

        if(!setShip(&ship, coords, field))
            continue;

        system("clear");
        showShipsToSet(shipsToSet);
        drawField(field);

        if(!isAgreed()) {
            reset(ship);
            continue;
        }

        delete(ship, shipsToSet);
        currShip++;
    }
}

void reset(Ship ship)
{
   for (int i = 0; i < ship.size; i++)
       ship.cells[i] -> shipId = -1; 
}

void showShipsToSet(int* ships)
{

    printf("    SHIPS TO SET      \n");
    printf("----------------------\n");
    printf("%4i%4i%4i%4i\n", ships[0], ships[1], ships[2], ships[3]);
    printf("----------------------\n");
    printf("%4c%4c%4c%4c\n", '^', '^', '^', '^');
    printf("%8c%4c%4c\n", 'O', 'O', 'O');
    printf("%12c%4c\n", 'O', 'O');
    printf("%16c\n\n\n", 'O');
}

char getSetMode (char gameMode)
{
    char setMode;

    if (gameMode == 'm') {
        setMode = 'a';
        return setMode;
    } 

    do {
        printf("SHIPS PLACEMENT\n"
               "a - AUTO\n" 
               "c - CUSTOM\n");

        setMode = getchar(); 
        clearBuff();

    } while (setMode != 'a' && setMode != 'c');
    printf("ITS OK\n");
    return setMode;
}

bool isEmpty (int* shipsLeft)
{
    for (int i = 0; i < 3; i++)
        if (shipsLeft[i] > 0)
            return false;
    
    return true;
}

int* getCoords(char setMode)
{
    static int* coords;

    if (setMode == 'a')
        coords = getMachineCoords();
    else
        coords = getUserCoords();
    printf("BEFORE\n");
    return coords;
}

int calcSize(int coords[4]) 
{
    int xDif = coords[2] - coords[0];
    int yDif = coords[3] - coords[1];

    return sqrt (xDif * xDif + yDif * yDif) + 1; 
}

bool contains (Ship ship, int* shipsToSet)
{
    if (shipsToSet[ship.size - 1] == 0)
        return false;
    else
        return true;
}


bool isAgreed(void) 
{
    char answ;
    
    printf("Are u agreed? (y/n): ");
    
    do {
        answ = getchar();
        clearBuff();
    } 
    while (answ != 'y' && answ != 'n' && answ != 'Y' && answ != 'N');

    if (answ == 'y' || answ == 'Y')
        return true;
    else
        return false;

}


void delete (Ship ship, int* shipsToSet)
{
    shipsToSet[ship.size - 1]--;
}

bool setShip (Ship* ship, int* coords, Cell field[][SIZE])
{
    ship -> cells = malloc (sizeof(Cell*) * ship -> size);

    int* fullCoords = getFullCoords(coords);
    
    for (int i = 0; i / 2 < ship -> size; i += 2)
    {
        ship -> cells[i / 2] = malloc(sizeof(Cell));

        ship -> cells[i / 2] = &field[ fullCoords[i + 1] ][ fullCoords[i] ];

        if (ship -> cells[i / 2] -> shipId != -1)
            return false;

        ship -> cells[i / 2] -> shipId = ship -> id; 
    }  
    return true;
}

int* getUserCoords()
{
    static int coords[4];

    do {
        
        printf ("Please input your top left coords: ");

        coords[0] = getchar();
        coords[1] = getchar() - '0';

        clearBuff();

        printf("%c,%i\n", coords[0], coords[1]);

        
        
        printf("Please input your bottom rigth coords: ");

        coords[2] = getchar();
        coords[3] = getchar() - '0';
        clearBuff();

        printf("%c,%i\n", coords[2], coords[3]);


        coords[0] = toupper(coords[0]) - 65;
        coords[2] = toupper(coords[2]) - 65;

    } while (coords[0] > 'j' || coords[0] < 0 || coords[2] > 'j' || coords[2] < 0 ||
             coords[1] > 9   || coords[1] < 0 || coords[3] > 9   || coords[3] < 0 ||
             !checkCoords(coords)); 
    
    return coords;
}

int* getFullCoords(int coords[4])
{
    int size = calcSize(coords); 

    static int* fullCoords;

    printf("________COOORDS_________\n");
    printf("%i, %i, %i, %i\n", coords[0], coords[1], coords[2], coords[3]);
    printf("________END_____________\n");

    fullCoords = malloc(sizeof(int) * size * 2);

    if (coords[0] == coords[2])    
    {
        for (int i = 0; i / 2 < size; i += 2)
        {
            fullCoords[i] = coords[0];
            fullCoords[i + 1] = coords[1] + i / 2;
        }
    }
    else
    {
        for (int i = 0; i / 2 < size; i += 2)
        {
            fullCoords[i] = coords[0] + i / 2;
            fullCoords[i + 1] = coords[1];
        }
    }
    printf("________COOORDS_________\n");
    printf("%i, %i\n", fullCoords[0], fullCoords[1]);
    printf("________END_____________\n");


    return fullCoords;
}

bool checkCoords(int coords[4])
{
    if (coords[0] == coords[2] && abs (coords[1] - coords[3] - 1) > 4)
        return false;
    else if (coords[1] == coords[3] && abs (coords[0] - coords[2] - 1) > 4)
        return false;
    else if (coords[0] != coords[2] && coords[1] != coords[3])
        return false;
    
    return true;
}
