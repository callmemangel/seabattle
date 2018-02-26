#include "game.h"
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

#define FIELD_W 11
#define FIELD_H 11

#define TEXT_W 18 
#define TEXT_H 1

#define INFO_W 14
#define INFO_H 8

#define RENDER_OPT 0

#define SLEEP_TIME 2


void startGame(Player* player_1, Player* player_2, char gameMode)
{
    
   GameWindow window;

   window.mainWindow = createWindow(WINDOW_W, WINDOW_H);
   window.gameField = createField(window.mainWindow, 2, 5, FIELD_W, FIELD_H);
   window.infoField = createField(window.mainWindow, 16, 5, 14, 8);
   window.textField = createField(window.mainWindow, 11, 2, TEXT_W, TEXT_H);


   initField(&window.dynamicField, window.gameField);
   initShipsInf(&window.dynamicInf, window.infoField);

   char p1Mode = 'c';
   char p2Mode = 'c';

   if (gameMode == 'm')
       p2Mode = 'a';


   while (!checkWin(player_1 -> field) && !checkWin (player_2 -> field)){  

       doShot(player_1, player_2, p1Mode, window);

       doShot(player_2, player_1, p2Mode, window);

   }

}

void setShipsInf(int* shipsInf)
{
    shipsInf[0] = 4;
    shipsInf[1] = 3;
    shipsInf[2] = 2;
    shipsInf[3] = 1;
}

void printText (char** field, char* text)
{
    sprintf(*field, "%s", text);
}

void updateField(char** windowField, Cell** field, bool hideShips)
{
    for (int i = 0; i < SIZE; i++) {             
       for (int j = 0; j < SIZE; j++) {        
                                          
            Cell cell = field[i][j];

            if (cell.shipId != -1 && !cell.isHitted && !hideShips) 
                windowField[i][j] = 'I';

            else if (cell.shipId != -1 && cell.isHitted)
                windowField[i][j] = 'X';

            else if (cell.isHitted)
                windowField[i][j] = 'O';

            else
                windowField[i][j] = '~';
       }
    }
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

void updateShipsInf(char** windowField, int* ships)
{
    sprintf(*windowField, "%3i%3i%3i%3i", ships[0], ships[1], ships[2], ships[3]);  
}

void initField(char*** dynamicField, char** field)
{
     const char letters[] = "ABCDEFGHIJ";
     char** buff = field;
     char* buf = *field;

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

     *dynamicField = createField(field, 1, 1, 10, 10);
}

void initShipsInf(char*** dynamicField, char** shipsInf)
{
    char** buff = shipsInf;
    char* buf = *shipsInf;

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

    *dynamicField = createField(shipsInf, 0, 2, 14, 1);

}


void doShot (Player* player_1, Player* player_2, char shotMode, GameWindow window)
{

    updateField(window.dynamicField, player_2 -> field, true);
    updateShipsInf(window.dynamicInf, player_2 -> shipsInf);
    

    while (true) {

           char move[NAME_LENGTH + strlen(" move")];
           sprintf(move, "%s move", player_1 -> name);

           clearTextField(window.textField);
           printText(window.textField, move);

           renderWindow(window.mainWindow, WINDOW_W, WINDOW_H, RENDER_OPT);

           int* shot = getShot(shotMode);

           if (player_2 -> field[shot[1]][shot[0]].isHitted)
               continue;

           player_2 -> field[shot[1]][shot[0]].isHitted = true;
            
           if (isHit (shot, player_2 -> field)) {

               int shipId = getShipId(shot, player_2 -> field);

               clearTextField(window.textField);
               printText(window.textField, "HITTED");  

               if (isKilled(shipId, player_2 -> ships)) {
                    player_2 -> ships[shipId].isKilled = true;

                    setEnvire(player_2 -> ships[shipId], player_2 -> field);

                    delete(player_2 -> ships[shipId], player_2 -> shipsInf);

                    updateShipsInf(window.dynamicInf, player_2 -> shipsInf);

                    clearTextField(window.textField);
                    printText(window.textField, "KILLED"); 
               }
               
               player_1 -> count++;

               updateField(window.dynamicField, player_2 -> field, true);

               renderWindow(window.mainWindow, WINDOW_W, WINDOW_H, RENDER_OPT);

               sleep(SLEEP_TIME);

               continue;

           }

           clearTextField(window.textField);
           printText(window.textField, "MISSED");

           updateField(window.dynamicField, player_2 -> field, true);
           renderWindow(window.mainWindow, WINDOW_W, WINDOW_H, RENDER_OPT);

           sleep(SLEEP_TIME);

           break;
    
       }

}

void clearTextField(char** textField)
{
    for (int i = 0; i < TEXT_H; i++)
        for (int j = 0; j < TEXT_W; j++)
            textField[i][j] = ' ';
}


int* getShot(char shotMode) 
{
    int* shot;
    if (shotMode == 'a')
        shot = getMachineShot();
    else
        shot = getUserShot();
    
    return shot;

}

int getShipId (int* shot, Cell** field)
{
    int x = shot[0];
    int y = shot[1];

    return field[y][x].shipId;

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

    if (field[y][x].shipId != -1)
        return true;

    return false;

}

bool isKilled(const int id, Ship* ships)
{
    Ship ship = ships[id];

    int size = ship.size;

    int hittedCells = 0;

    for (int i = 0; i < size; i++) 
        if (ship.cells[i] -> isHitted)
            hittedCells++;

    if (size == hittedCells)
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
            field[i][j].isHitted = false;
            field[i][j].shipId = -1;
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
            
            field[i][j].isHitted = true; 

        }
            
    }

}

