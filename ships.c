#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "machine.h"
#include "player.h"
#include "animation.h"
#include "structs.h"
#include "window.h"
#include "ships.h"
#include "game.h"
#include "textfield.h"
#include "cursor.h"


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
    
    updateShipsField(window.ships_field, player -> field, false);

    Cell** prev_field;
    
    char set_mode = getSetMode(*player); 

    setShipsLeft(player -> ships_left);
    updateShipsLeft(window.ships_left, player -> ships_left);

    if (!player -> is_machine)
        renderWindow(window.root, RENDER_OPT);

    int curr_ship = 0;

    srand(time(NULL));

    while (!isEmpty (player -> ships_left)) {

        int* coords = getCoords(set_mode, window, player -> ships_left);   

        if (!checkCoords(coords, player -> field))
            continue; 

        Ship* ship = &player -> ships[curr_ship];

        prev_field = storeField(player -> field, prev_field);

        initShip (ship, curr_ship, coords);

        if (!contains(*ship, player -> ships_left))
            continue;

        if (!player -> is_machine)
            renderWindow(window.root, RENDER_OPT);

        setShip(ship, coords, player -> field);

        deleteShip(*ship, player -> ships_left);
        updateShipsLeft(window.ships_left, player -> ships_left);
        updateShipsField(window.ships_field, player -> field, false);

        if (!player -> is_machine)  {

            Animation splash =  createShipSetSplashAnimation(ship -> cells[0] -> x,
                                                             ship -> cells[0] -> y, *ship);
        
            renderAnimationOnWindow(splash, window.game_field, window.root);
            renderWindow(window.root, RENDER_OPT);

            if (!isAgreed()) {
                player -> ships_left[ship -> size - 1]++;
                unsetShip(*ship);
                updateShipsField(window.ships_field, prev_field, false);
                updateShipsLeft(window.ships_left, player -> ships_left);
                renderWindow(window.root, RENDER_OPT); continue;
            }
        }

        
        if (!player -> is_machine)
            renderWindow(window.root, RENDER_OPT);

        curr_ship++;
    }
}

char getSetMode (Player player)
{
    system("clear");

    char set_mode;

    if (player.is_machine) {
        set_mode = 'a';
        return set_mode;
    } 

    return getCursorSetMode(player);
}

char getCursorSetMode(Player player)
{
    Window window = createWindow(40, 20);

    Window menu = createField(window, 14, 6, 14, 6);

    Window yes_no = createField(menu, 0, 3, 1, 3);

    sprintf(menu.field[0], "%s ship set", player.name);

    sprintf(menu.field[3], ">  custom");
    sprintf(menu.field[5], ">  auto  ");

    Cursor cursor;
    initCursorOnWindow(&cursor, yes_no, '>', 'G', 1, 1);

    renderCursor(cursor);
    renderWindow(window, 0);
    
    int position = 1;

    while (true) {
    
        int input = listenInput();

        char vector = '\0';

        switch (input) {
            
           case '\033':
              vector = getArrowVector();

              if (vector == 'd' && position < 2) {
                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  position++;
              }

              else if (vector == 'u' && position > 1) {
                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  position--;
              }
              vector = '\0';

              break;

           case '\n':
              if (position == 1) {
                  freeCursor(cursor);
                  return 'c';
              }
              else {
                  freeCursor(cursor);
                  return 'a';
              }

              break;
        }

        renderWindow(window, 0);
    }
}
 
void setShipsLeft(int* ships_left)
{
    ships_left[0] = 4;
    ships_left[1] = 3;
    ships_left[2] = 2;
    ships_left[3] = 1;
}

bool isEmpty (int* ships_left)
{
    for (int i = 0; i < 4; i++)
        if (ships_left[i] > 0)
            return false;
    
    return true;
}

bool contains (Ship ship, int* shipsToSet)
{
    if (shipsToSet[ship.size - 1] == 0)
        return false;
    else
        return true;
}


int* getCoords(char set_mode, GameWindow window, int* ships_left)
{
    int* coords;
    if (set_mode == 'a')
        coords = getMachineCoords();
    else
        coords = getCursorCoords(window, ships_left);

    return coords;
}

int* getCursorCoords(GameWindow window, int* ships_left) 
{
    static int coords[4];

    int size = chooseShip(window, ships_left);

    ships_left[size - 1]--;
    updateShipsLeft(window.ships_left, ships_left);
    ships_left[size - 1]++;

    
    Cursor cursor;
 
    initCursorOnWindow(&cursor, window.ships_field, 'I', 'C', 1, size);
    renderCursor(cursor);
    renderWindow(window.root, 0);

    while(true) {

        int input = listenInput();

        char vector = '\0';

        switch (input) {
            
           case '\033':
              vector = getArrowVector();
              break;

           case '\n':
              coords[0] = cursor.curr_x;
              coords[1] = cursor.curr_y;

              if (cursor.width >= cursor.height) {
                  coords[2] = cursor.curr_x + size - 1;
                  coords[3] = cursor.curr_y;
              }

              else if (cursor.width < cursor.height) {
                  coords[2] = cursor.curr_x;
                  coords[3] = cursor.curr_y + size - 1; 
              }
              recoverStoredArea(cursor);
              freeCursor(cursor); 
              return coords;
              break;

            case 'r':

              if (cursor.width >= cursor.height && cursor.curr_y + cursor.width - 1<= 9) {
                    recoverStoredArea(cursor);
                    int tmp = cursor.width;
                    cursor.width = cursor.height;
                    cursor.height = tmp;
                    storeBeforeRender(&cursor);
              }

              else if (cursor.width < cursor.height && cursor.curr_x + cursor.height - 1 <= 9) {
                    recoverStoredArea(cursor);
                    int tmp = cursor.width;
                    cursor.width = cursor.height;
                    cursor.height = tmp;
                    storeBeforeRender(&cursor);

              }
              break;

           default:
              vector = '\0';
        }
        moveCursor(&cursor, vector);
        renderWindow(window.root, 0);
    }  
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

int chooseShip(GameWindow window, int* ships_left)
{

    Cursor cursor;
    initCursorOnWindow(&cursor, window.info_field, 'I', 'G', 1, 1);
    cursor.curr_x = 2;
    cursor.curr_y = 4;
    storeBeforeRender(&cursor);

    renderCursor(cursor);
    renderWindow(window.root, 0);

    
    int position = 1;

    while (true) {
    
        int input = listenInput();

        char vector = '\0';

        switch (input) {
            
           case '\033':
              vector = getArrowVector();

              if (vector == 'r' && position < 4) {
                  recoverStoredArea(cursor); 
                  cursor.height++;
                  storeBeforeRender(&cursor);

                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  position++;
              }

              else if (vector == 'l' && position > 1) {
                  recoverStoredArea(cursor); 
                  cursor.height--;
                  storeBeforeRender(&cursor);
                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  moveCursor(&cursor, vector);
                  position--;
              }
              vector = '\0';

              break;

           case '\n':
              if (ships_left[position - 1] == 0)
                  break;
              recoverStoredArea(cursor);
              freeCursor(cursor);
              return position;
              break;

           default:
              vector = '\0';
        
        }
        renderWindow(window.root, 0);
    }
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

bool checkCoords(int coords[4], Cell** field)
{
    if (!checkSize (coords))
        return false;

    if(!checkEnv (coords, field))
        return false;

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


void initShip (Ship* ship, const int id, int* coords)
{
    ship -> id = id;
    ship -> size = calcSize (coords);
    ship -> is_killed = false; 
    ship -> cells = malloc (sizeof(Cell*) * ship -> size);
}

void initCells (Cell** field)
{
    for (int i = 0; i < SHIPS_FIELD_SIZE; i++)
        for (int j = 0; j < SHIPS_FIELD_SIZE; j++)
        {
            field[i][j].x = j;
            field[i][j].y = i;
            field[i][j].is_hitted = false;
            field[i][j].ship_id = -1;
        }
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

void unsetShip(Ship ship)
{
   for (int i = 0; i < ship.size; i++)
       ship.cells[i] -> ship_id = -1; 
}

void deleteShip (Ship ship, int* shipsToSet)
{
    shipsToSet[ship.size - 1]--;
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

        clearInputBuff();
    } 
    while (answ != 'y' && answ != 'n' && answ != 'Y' && answ != 'N');

    if (answ == 'y' || answ == 'Y')
        return true;
    else
        return false;

}


bool isHit (int* shot, Cell** field)
{
    int x = shot[0];
    int y = shot[1];

    if (field[y][x].ship_id != -1)
        return true;

    return false;

}

bool isKilled(const int id, Ship* ships)
{
    Ship ship = ships[id];

    int size = ship.size;

    int hitted_cells = 0;

    for (int i = 0; i < size; i++) 
        if (ship.cells[i] -> is_hitted)
            hitted_cells++;

    if (size == hitted_cells)
        return true;

    return false;

}

int getShipId (int* shot, Cell** field)
{
    int x = shot[0];
    int y = shot[1];

    return field[y][x].ship_id;

}


int* createSetArea(Ship ship)
{
    static int setArea[4];

    setArea[0] = ship.cells[0] -> x - 1;
    setArea[1] = ship.cells[0] -> y - 1;
    setArea[2] = ship.cells[ship.size - 1] -> x + 1;
    setArea[3] = ship.cells[ship.size - 1] -> y + 1;

    return setArea;
}

void setEnvire(Ship ship, Cell** field)
{
    int* setArea = createSetArea(ship);

    for (int i = setArea[1]; i <= setArea[3]; i++) {

        for (int j = setArea[0]; j <= setArea[2]; j++) {

            if (i < 0 || j < 0 || i > 9 || j > 9){
               continue;
            }
            
            field[i][j].is_hitted = true; 
        }
    }
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
