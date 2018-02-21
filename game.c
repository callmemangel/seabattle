#include "game.h"
#include "machine.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void startGame(Player player_1, Player player_2, char gameMode)
{
   while (!checkWin(player_1.field) && !checkWin (player_2.field)){  

       doShot(player_1, player_2, gameMode);

       doShot(player_2, player_2, gameMode);

   }

}

void drawField(Cell field[][SIZE])
{
    const char letters[] = "ABCDEFGHIJ";

    printf("%2c", ' ');

    for (int i = 0; i < 10; i++)
        printf("%2c", letters[i]);

    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%2i", i);
        for (int j = 0; j < 10; j++)
            if (field[i][j].shipId != -1)
                printf("%2c", 'I');
            else
                printf("%2c", '~');
        printf("\n");    
    }
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

bool isHit (int shot, Cell field[][SIZE])
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

void initCells (Cell field[][SIZE])
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

bool checkWin (Cell field[][SIZE]) {}

void drawHitField(Cell field[][SIZE]) {}

int getUserShot() {}

void clearBuff(void) 
{
    while(getchar() != '\n');
}
