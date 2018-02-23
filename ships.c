#include "machine.h"
#include "window.h"
#include "ships.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define WINDOW_W 30 
#define WINDOW_H 15 

#define GAME_FIELD_W 11
#define GAME_FIELD_H 11

#define SHIPS_INF_W 14
#define SHIPS_INF_H 8

#define RENDER_OPT 0

void setShips (Cell** field, Ship* ships, char gameMode)
{

    char** window    = createWindow(WINDOW_W, WINDOW_H);
    char** gameField = createField(window, 2, 2, GAME_FIELD_W, GAME_FIELD_H);
    char** shipsInf  = createField(window, 15, 2, SHIPS_INF_W, SHIPS_INF_H);

    char** dynamicField;
    char** dynamicShipsInf;

    Cell** prevField;
    
    int shipsToSet[] = {4, 3, 2, 1};

    char setMode = getSetMode(gameMode);

    int currShip = 0;

    initField(&dynamicField, gameField);
    initShipsInf(&dynamicShipsInf, shipsInf);


    renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);


    srand(time(NULL));

    while (!isEmpty (shipsToSet)) {



        int* coords = getCoords(setMode, coords);   

        if (!checkCoords(coords, field))
            continue; 


        renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);

        Ship ship   = ships[currShip];
        prevField   = storeField(field, prevField);

        initShip (&ship, currShip, coords);

        if (!contains(ship, shipsToSet))
            continue;

        setShip(&ship, coords, field);
           
        
        updateField(dynamicField, field);
        
        renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);

        if (!isAgreed()) {

            reset(ship);
            updateField(dynamicField, prevField);
            renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);
            continue;
        }

        delete(ship, shipsToSet);
        updateShipsInf(dynamicShipsInf, shipsToSet);

        renderWindow(window, WINDOW_W, WINDOW_H, RENDER_OPT);

        currShip++;
    }
}

void initShip (Ship* ship, const int id, int* coords)
{
    ship -> id = id;
    ship -> size = calcSize (coords);
    ship -> isKilled = false; 
    ship -> cells = malloc (sizeof(Cell*) * ship -> size);
}
    
void reset(Ship ship)
{
   for (int i = 0; i < ship.size; i++)
       ship.cells[i] -> shipId = -1; 
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

        if (setMode != '\n')
            clearBuff();

    } while (setMode != 'a' && setMode != 'c');

    return setMode;
}

bool isEmpty (int* shipsLeft)
{
    for (int i = 0; i < 4; i++)
        if (shipsLeft[i] > 0)
            return false;
    
    return true;
}

int* getCoords(char setMode, int* coords)
{
    if (setMode == 'a')
        coords = getMachineCoords();
    else
        coords = getUserCoords();

    return coords;
}

int calcSize(int coords[4]) 
{
    int dist = calcDist(coords[0], coords[1], coords[2], coords[3]);

    int size = dist + 2;

    return size;
}

int calcDist(int x1, int y1, int x2, int y2)
{
    int xDif = x2 - x1;
    int yDif = y2 - y1;

    return sqrt (xDif * xDif + yDif * yDif) - 1; 
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

        if (answ == '\n') {
            answ = 'y';
            break; 
        }

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

void setShip (Ship* ship, int* coords, Cell** field)
{

    int* fullCoords = getFullCoords(coords);
    
    for (int currCell = 0, coordPos = 0; currCell < ship -> size; currCell++, coordPos += 2)
    {
        ship -> cells[currCell] = malloc(sizeof(Cell));

        int fx = fullCoords[coordPos];
        int fy = fullCoords[coordPos + 1];

        ship -> cells[currCell] = &field [fy][fx];

        ship -> cells[currCell] -> shipId = ship -> id; 
    }  
}

int* getUserCoords()
{
    static int coords[4];

    do {
        
        printf ("Please input your top left coords: ");

        coords[0] = getchar();
        coords[1] = getchar() - '0';

        clearBuff();

        printf("Please input your bottom rigth coords: ");

        coords[2] = getchar();
        coords[3] = getchar() - '0';
        clearBuff();

        coords[0] = toupper(coords[0]) - 65;
        coords[2] = toupper(coords[2]) - 65;

    } while (!validCoords(coords));
              
     
    return coords;
}

int* getFullCoords(int coords[4])
{
    int size = calcSize(coords); 

    static int* fullCoords;

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

    return fullCoords;
}



bool checkCoords(int coords[4], Cell** field)
{
    if (!checkSize (coords))
        return false;

    if(!checkEnv (coords, field))
        return false;

    return true;
}

bool validCoords(int coords[4])
{
    
   if (coords[0] > 9   || coords[0] < 0 || coords[2] > 9   || coords[2] < 0 ||
       coords[1] > 9   || coords[1] < 0 || coords[3] > 9   || coords[3] < 0 )
   {
            return false;
   }

   return true;
}

bool checkSize (int coords[4])
{
    int x1 = coords[0];
    int y1 = coords[1];
    int x2 = coords[2];
    int y2 = coords[3];

    if (x1 == x2 && abs (y1 - y2 - 1) > 4)
        return false;

    else if (y1 == y2 && abs (x1 - x2 - 1) > 4)
        return false;

    else if (x1 != x2 && y1 != y2)
        return false;

    else
        return true;

}

bool checkEnv(int coords[4], Cell** field)
{
    int checkArea[4];

    int x1 = coords[0];
    int y1 = coords[1];
    int x2 = coords[2];
    int y2 = coords[3];


    checkArea[0] = x1 - 1;
    checkArea[1] = y1 - 1;
    checkArea[2] = x2 + 1;
    checkArea[3] = y2 + 1;

    for (int i = checkArea[1]; i <= checkArea[3]; i++) {

        for (int j = checkArea[0]; j <= checkArea[2]; j++) {

            if (i < 0 || j < 0 || i > 9 || j > 9){
               continue;
            }

            if (field[i][j].shipId != -1)
               return false; 
        }
            
    }

    return true;

}
