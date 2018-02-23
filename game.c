#include "game.h"
#include "machine.h"
#include "window.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void startGame(Player player_1, Player player_2, char gameMode)
{
   while (!checkWin(player_1.field) && !checkWin (player_2.field)){  

       doShot(player_1, player_2, gameMode);

       doShot(player_2, player_2, gameMode);

   }

}

void updateField(char** windowField, Cell** field)
{
    for (int i = 0; i < SIZE; i++) {             
       for (int j = 0; j < SIZE; j++) {        
                                          
            Cell cell = field[i][j];

            if (cell.shipId != -1 && !cell.isHitted) 
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


void doShot (Player player_1, Player player_2, char gameMode)
{

    while (true) {

           int shot = getShot(gameMode);
            
           if (isHit (shot, player_2.field)) {

               printf("%s MISSED\n", player_1.name);
               break;

           }

           printf("%s HITTED\n", player_1.name);

           drawHitField(player_1.field);

           player_1.count++; 
       }

}


int getShot(int gameMode) 
{
    char shot;

    if (gameMode == 'm')
        shot = getMachineShot();
    else
        shot = getUserShot();

    return shot;
}

//void reset(void)
//{
 //   p1Count = 0;
  //  p2Count = 0;

   // free(player_1);
    //free(player_2);

   // gameMode = '\0';

//}

bool isHit (int shot, Cell** field)
{



}


char* getPlayerName(char gameMode)
{
    static char name[10];

    if (gameMode == 'm') {
        strcpy(name, "MACHINE");
        return name;
    }

    printf("Input your name: ");

    fgets(name, 10, stdin);

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

void drawHitField(Cell** field) {}

int getUserShot() {}

void clearBuff(void) 
{
    while(getchar() != '\n');
}
