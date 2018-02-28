#include "game.h"
#include "cursor.h"
#include "structs.h"
#include "machine.h"
#include "window.h"
#include "ships.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define WINDOW_W 30 
#define WINDOW_H 20 

#define GAME_FIELD_W 11
#define GAME_FIELD_H 11

#define SHIPS_INF_W 14
#define SHIPS_INF_H 8

#define TEXTFIELD_W 10
#define TEXTFIELD_H 1 

#define RENDER_OPT 0

#define SLEEP_TIME 2

void clearTextField(Window text_field)
{
    for (int i = 0; i < text_field.height; i++)
        for (int j = 0; j < text_field.width; j++)
            text_field.field[i][j] = ' ';

}

void printToTextField(Window text_field, const char* text, char color)
{
    clearTextField(text_field);

    for (int i = 0; i < text_field.height; i++)
        for (int j = 0; j < text_field.width; j++) {
            if (i * text_field.height + j == strlen(text))
                return;

            text_field.field[i][j] = text[i * text_field.height + j];
            text_field.color_map[i][j] = color;
        }

}


void startGame(Player* player_1, Player* player_2)
{
    
   GameWindow window;

   initGameField (&window);



   while (!checkWin(player_1 -> field) && !checkWin (player_2 -> field)){  
        
       doShot(player_1, player_2, window);

       doShot(player_2, player_1, window);

   }

}

void setShipsLeft(int* ships_left)
{
    ships_left[0] = 4;
    ships_left[1] = 3;
    ships_left[2] = 2;
    ships_left[3] = 1;
}

void updateShipsField(Window window, Cell** field, bool hide_ships)
{
    for (int i = 0; i < SIZE; i++) {             
       for (int j = 0; j < SIZE; j++) {        
                                          
            Cell cell = field[i][j];

            if (cell.ship_id != -1 && !cell.is_hitted && !hide_ships) {
                window.field[i][j] = 'I';
                window.color_map[i][j] = 'g';
            }

            else if (cell.ship_id != -1 && cell.is_hitted) {
                window.field[i][j] = 'X';
                window.color_map[i][j] = 'r';
            }

            else if (cell.is_hitted) {
                window.field[i][j] = 'O';
                window.color_map[i][j] = 'c';
            }

            else {
                window.field[i][j] = '~';
                window.color_map[i][j] = 'b';
            }
       }
    }
}

void initGameField(GameWindow* window)
{
    window -> root = createWindow(WINDOW_W, WINDOW_H);

    window -> game_field  = createField(window -> root, 2, 2, GAME_FIELD_W, GAME_FIELD_H);
    window -> info_field  = createField(window -> root, 15, 2, SHIPS_INF_W, SHIPS_INF_H);
    window -> text_field  = createField(window -> root, 10, 0, TEXTFIELD_W, TEXTFIELD_H);


    window -> ships_field = initMapField(window -> game_field);

    window -> ships_left = initInfoField(window -> info_field);
}


Cell** storeField (Cell** field, Cell** tmp)
{
    tmp = mallocField(tmp);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tmp[i][j] = field[i][j];

    return tmp;
}

Cell** mallocField (Cell** field)
{
    field = malloc(sizeof(Cell*) * SIZE);

    for (int i = 0; i < SIZE; i++)
        field[i] = malloc(sizeof(Cell) * SIZE);

    return field;
}

void updateShipsLeft(Window ships_left, int* ships)
{
    sprintf(*(ships_left.field), "%3i%3i%3i%3i", ships[0], ships[1], ships[2], ships[3]);  

    for (int i = 0; i < ships_left.width; i++)
        if (ships_left.field[0][i] == '0')
            ships_left.color_map[0][i] = 'g';
}

Window initMapField(Window game_field)
{
     Window ships_field;
     
     const char letters[] = "ABCDEFGHIJ";
     char** buff = game_field.field;
     char* buf = *buff;

     *buf++ = ' ';

     for (int i = 0; i < 10; i++)
         *buf++ = letters[i];

     buf = *++buff;

     for (int i = 0; i < 10; i++) {

         *buf++ = i + '0';

          for (int j = 0; j < 10; j++)
              *buf++ = '~';

          buf = *++buff;
     }

     ships_field = createField(game_field, 1, 1, 10, 10);
     return ships_field;
}

Window initInfoField(Window info_field)
{
    
    char** buff = info_field.field;
    char* buf = *buff;

    sprintf(buf, "     SHIPS    ");
    buf = *++buff;

    sprintf(buf, "              ");
    buf = *++buff;

    sprintf(buf, "  4  3  2  1  ");
    buf = *++buff; 

    sprintf(buf, "              ");
    buf = *++buff; 

    sprintf(buf, "  I  I  I  I  ");
    buf = *++buff; 

    sprintf(buf, "     I  I  I  ");
    buf = *++buff; 

    sprintf(buf, "        I  I  ");
    buf = *++buff; 

    sprintf(buf, "           I  ");
    buf = *++buff;

    Window ships_left = createField(info_field, 0, 2, 14, 1);

    return ships_left;
}


void doShot (Player* player_1, Player* player_2, GameWindow window)
{

    bool hide_ships = true;

    updateShipsField(window.ships_field, player_2 -> field, hide_ships);
    printf("SHIPS FIELD UPDATED\n");
    updateShipsLeft(window.ships_left, player_2 -> ships_left);
    printf("SHIPS INFO UPDATED\n");
    
    while (true) {

           char move[NAME_LENGTH + strlen(" move")];
           sprintf(move, "%s move", player_1 -> name);
           printToTextField(window.text_field, move, 'w');

           renderWindow(window.root, RENDER_OPT);

           int* shot;
           if (player_1 -> is_machine)
                shot = getShot(window, 'a');
           else
                shot = getShot(window, 'c');


           if (player_2 -> field[shot[1]][shot[0]].is_hitted)
               continue;

           player_2 -> field[shot[1]][shot[0]].is_hitted = true;
            
           if (isHit (shot, player_2 -> field)) {

               player_1 -> count++;

               int shipId = getShipId(shot, player_2 -> field);

               printToTextField(window.text_field, "HITTED", 'r');  

               if (isKilled(shipId, player_2 -> ships)) {

                    player_2 -> ships[shipId].is_killed = true;

                    setEnvire(player_2 -> ships[shipId], player_2 -> field);

                    delete(player_2 -> ships[shipId], player_2 -> ships_left);

                    updateShipsLeft(window.ships_left, player_2 -> ships_left);

                    printToTextField(window.text_field, "KILLED", 'r'); 
               }
               
               updateShipsField(window.ships_field, player_2 -> field, true);

               renderWindow(window.root, RENDER_OPT);

               sleep(SLEEP_TIME);

               continue;

           }

           printToTextField(window.text_field, "MISSED", 'c');

           updateShipsField(window.ships_field, player_2 -> field, true);
           renderWindow(window.root, RENDER_OPT);

           sleep(SLEEP_TIME);

           break;
    
       }

}

int* getShot(GameWindow window, char shotMode) 
{
    int* shot;
    if (shotMode == 'a')
        shot = getMachineShot();
    else {
        shot = getCursorShot(window);
    }
    
    return shot;

}

int* getCursorShot(GameWindow window)
{

    static int shot[2];

    Cursor cursor;

    initCursorOnWindow(&cursor, window.ships_field, 'm', 'r');
    renderCursor(cursor);
    renderWindow(window.root, RENDER_OPT);

    while(true) {
    
        char value = listenInput();
        char vector;

        switch(value) {
        
            case '\033':
                vector = getArrowVector();
                break;
            case '\n':
                shot[0] = cursor.curr_x;
                shot[1] = cursor.curr_y;
                freeCursor(cursor);
                return shot;
                break;

            default:
                vector = '0';
        
        } 
        moveCursor(&cursor, vector, false);
        renderWindow(window.root, RENDER_OPT);
    }


}

int getShipId (int* shot, Cell** field)
{
    int x = shot[0];
    int y = shot[1];

    return field[y][x].ship_id;

}

//void reset(void)
//{
 //   p1Count = 0;
  //  p2Count = 0;

   // free(player_1);
    //free(player_2);

   // gameMode = '\0';

//}

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


char* getPlayerName(char* name, char opt)
{

    if (opt == 'a') {
        strcpy(name, "MACHINE");
        return name;
    }

    fgets(name, NAME_LENGTH, stdin);

    name[strlen(name) - 1] = '\0';

    return name;

}

char getGameMode(void)
{
    char gameMode;

    do {
        printf("CHOOSE GAMEMODE\n"
               "p - PLAYER VS PLAYER\n" 
               "m - PLAYER VS MACHINE\n");

        gameMode = getchar();
        if (gameMode != '\n')
            clearBuff(); 

   } while (gameMode != 'p' && gameMode != 'm');

   return gameMode;
}


bool wannaRepeat(void)
{
    char answ;

    printf("Want repeat? (y/n):");

    do {
        answ = getchar();
        clearBuff(); 
    } while (answ != 'y' && answ != 'n' && answ != 'Y' && answ != 'N');

    if (answ == 'y' || answ == 'Y')
        return true;
    else
        return false;
}

void initCells (Cell** field)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            field[i][j].x = j;
            field[i][j].y = i;
            field[i][j].is_hitted = false;
            field[i][j].ship_id = -1;
        }
}

bool checkWin (Cell** field) {}

int* getUserShot() 
{
    static int shot[2];

    do {

        printf("Your Coords: ");

        int x = toupper(getchar()) - 65;
        int y = getchar() - '0';

        if (y != '\n') 
            clearBuff();

        shot[0] = x;
        shot[1] = y;

    } while (!validCoords(shot, 2));

    return shot;

}

void clearBuff(void) 
{
    while(getchar() != '\n');
}

void setEnvire(Ship ship, Cell** field)
{
    int setArea[4];

    setArea[0] = ship.cells[0] -> x - 1;
    setArea[1] = ship.cells[0] -> y - 1;
    setArea[2] = ship.cells[ship.size - 1] -> x + 1;
    setArea[3] = ship.cells[ship.size - 1] -> y + 1;

    for (int i = setArea[1]; i <= setArea[3]; i++) {

        for (int j = setArea[0]; j <= setArea[2]; j++) {

            if (i < 0 || j < 0 || i > 9 || j > 9){
               continue;
            }
            
            field[i][j].is_hitted = true; 

        }
            
    }

}

