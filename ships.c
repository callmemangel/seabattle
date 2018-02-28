#include "machine.h"
#include "structs.h"
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
#define WINDOW_H 20 

#define GAME_FIELD_W 11
#define GAME_FIELD_H 11

#define SHIPS_INF_W 14
#define SHIPS_INF_H 8

#define TEXTFIELD_W 10
#define TEXTFIELD_H 1 

#define RENDER_OPT 0

void setShips (Player* player)
{

    GameWindow window;
    initGameField(&window);

    Cell** prev_field;
    
    char set_mode = getSetMode(*player); 

    renderWindow(window.root, RENDER_OPT);

    int curr_ship = 0;

    srand(time(NULL));

    while (!isEmpty (player -> ships_left)) {

        int* coords = getCoords(set_mode, coords);   

        if (!checkCoords(coords, player -> field))
            continue; 

        Ship* ship = &player -> ships[curr_ship];

        prev_field = storeField(player -> field, prev_field);

        initShip (ship, curr_ship, coords);

        if (!contains(*ship, player -> ships_left))
            continue;

        renderWindow(window.root, RENDER_OPT);

        setShip(ship, coords, player -> field);
        
        updateShipsField(window.ships_field, player -> field, false);
        
        renderWindow(window.root, RENDER_OPT);

        if (!player -> is_machine)
            if (!isAgreed()) {

                reset(*ship);
                updateShipsField(window.ships_field, prev_field, false);
                renderWindow(window.root, RENDER_OPT);
                continue;
            }

        delete(*ship, player -> ships_left);
        updateShipsLeft(window.ships_left, player -> ships_left);

        renderWindow(window.root, RENDER_OPT);

        curr_ship++;
    }
}

void initShip (Ship* ship, const int id, int* coords)
{
    ship -> id = id;
    ship -> size = calcSize (coords);
    printf("SHIP WHERE ID = %i SIZE = %i\n", ship -> id, ship -> size);
    ship -> is_killed = false; 
    ship -> cells = malloc (sizeof(Cell*) * ship -> size);
}
    
void reset(Ship ship)
{
   for (int i = 0; i < ship.size; i++)
       ship.cells[i] -> ship_id = -1; 
}

char getSetMode (Player player)
{
    system("clear");

    char set_mode;

    if (player.is_machine) {
        set_mode = 'a';
        return set_mode;
    } 

    do {
        printf("%s SHIPS PLACEMENT\n"
               "a - AUTO\n" 
               "c - CUSTOM\n", player.name);

        set_mode = getchar(); 

        if (set_mode != '\n')
            clearBuff();

    } while (set_mode != 'a' && set_mode != 'c');

    return set_mode;
}

bool isEmpty (int* ships_left)
{
    for (int i = 0; i < 4; i++)
        if (ships_left[i] > 0)
            return false;
    
    return true;
}

int* getCoords(char set_mode, int* coords)
{
    if (set_mode == 'a')
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

        int f_x = fullCoords[coordPos];
        int f_y = fullCoords[coordPos + 1];

        ship -> cells[currCell] = &field [f_y][f_x];

        ship -> cells[currCell] -> ship_id = ship -> id; 
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

    } while (!validCoords(coords, 4));
              
     
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

bool validCoords(int* coords, int number)
{
   for (int i = 0; i < number; i++) {

        if (coords[i] > 9 || coords[i] < 0)  {
            return false;
        }

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

            if (field[i][j].ship_id != -1)
               return false; 
        }
            
    }

    return true;

}
