#include "game.h"
#include "cursor.h"
#include "animation.h"
#include "structs.h"
#include "getch.h"
#include "machine.h"
#include "time.h"
#include "window.h"
#include "ships.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define WINDOW_W 40 
#define WINDOW_H 20 

#define GAME_FIELD_W 11
#define GAME_FIELD_H 12

#define SHIPS_INF_W 14
#define SHIPS_INF_H 8

#define TEXTFIELD_W 10
#define TEXTFIELD_H 1 

#define RENDER_OPT 0

#define SLEEP_TIME 700000

#define GAME_FIELD_PAD_X 6 
#define GAME_FIELD_PAD_Y 4

#define SHIPS_IFN_PAD_X 18
#define SHIPS_IFN_PAD_Y 5

#define TEXTFIELD_PAD_X 15
#define TEXTFIELD_PAD_Y 2

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


   while (true) {  
        
       doShot(player_1, player_2, window);

       if (isWin(player_2 -> ships))
           break;

       doShot(player_2, player_1, window);
       if (isWin(player_1 -> ships))
           break;
   }

   if (isWin(player_1 -> ships))
       renderWinnerWindow(*player_2, window.root);
   else
       renderWinnerWindow(*player_1, window.root);

}

void setShipsLeft(int* ships_left)
{
    ships_left[0] = 4;
    ships_left[1] = 3;
    ships_left[2] = 2;
    ships_left[3] = 1;
}

void renderWinnerWindow(Player player, Window window)
{
    for (int i = 0; i < window.height; i++)
        for (int j = 0; j < window.width; j++) {
            window.field[i][j] = ' ';
            window.color_map[i][j] = ' ';
        }
    
    Window textfield0 = createField(window, 11, 2, 15, 1);
    Window textfield1 = createField(window, 17, 9, 15, 1);
    Window textfield2 = createField(window, 13, 11, 15, 1);
    Window textfield3 = createField(window, 8, 19, 24, 1);

    Animation* animations = NULL;
    int a = 0;
    int* size = &a;


    srand(time(NULL));
    
    char* rand_colors = "RCBY";

    while(getch_unin() != '\n')
    {
        int rand_num = rand() % 3;
        
        if (rand_num == 1) {
           size = addAnimation(&animations, createSalutAnimation(rand() % (window.width - 14), 
                                                                 rand() % 10, rand_colors[rand() % 4]));
        } 
        renderAnimationArrayOnWindow(animations, window, size, 'c');

        printToTextField(textfield0, "CONGRATULATIONS", 'R');
        printToTextField(textfield1, player.name, 'W');
        printToTextField(textfield2, "YOU R WINNER", 'W');
        printToTextField(textfield3, "PRESS ENTER TO CONTINUE", 'w');
        renderWindow(window, 0);
        usleep(100000);

    }

    for (int i = 0; i < window.height; i++)
        for (int j = 0; j < window.width; j++) {
            window.field[i][j] = ' ';
            window.color_map[i][j] = ' ';
        }
 
}

void updateShipsField(Window window, Cell** field, bool hide_ships)
{
    for (int i = 0; i < SIZE; i++) {             
       for (int j = 0; j < SIZE; j++) {        
                                          
            Cell cell = field[i][j];

            if (cell.ship_id != -1 && !cell.is_hitted && !hide_ships) {
                window.field[i][j] = 'I';
                window.color_map[i][j] = 'G';
            }

            else if (cell.ship_id != -1 && cell.is_hitted) {
                window.field[i][j] = 'X';
                window.color_map[i][j] = 'R';
            }

            else if (cell.is_hitted) {
                window.field[i][j] = 'O';
                window.color_map[i][j] = 'C';
            }

            else {
                window.field[i][j] = '~';
                window.color_map[i][j] = 'B';
            }
       }
    }
}

void initGameField(GameWindow* window)
{
    window -> root = createWindow(WINDOW_W, WINDOW_H);

    window -> game_field  = createField(window -> root, GAME_FIELD_PAD_X, GAME_FIELD_PAD_Y, GAME_FIELD_W, GAME_FIELD_H);
    window -> info_field  = createField(window -> root, SHIPS_IFN_PAD_X, SHIPS_IFN_PAD_Y, SHIPS_INF_W, SHIPS_INF_H);
    window -> text_field  = createField(window -> root, TEXTFIELD_PAD_X, TEXTFIELD_PAD_Y, TEXTFIELD_W, TEXTFIELD_H);


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
    printf("TRYING TO RENEW VALUES\n");
    printf("SHIPS[0] = %i\n", ships[0]);
    printf("SHIPS[1] = %i\n", ships[1]);
    printf("SHIPS[2] = %i\n", ships[2]);
    printf("SHIPS[3] = %i\n", ships[3]);
    renderWindow(ships_left, 1);
    printf("WINDOW REnDeres\n");
    sprintf(*(ships_left.field), "%3i%3i%3i%3i", ships[0], ships[1], ships[2], ships[3]);  
    printf("RENEWED\n");

    for (int i = 0; i < ships_left.width; i++)
        if (ships_left.field[0][i] == '0')
            ships_left.color_map[0][i] = 'G';
        else
            ships_left.color_map[0][i] = 'w';
}

char getCursorShipSet(Player player)
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
                  moveCursor(&cursor, vector, false);
                  moveCursor(&cursor, vector, false);
                  position++;
              }

              else if (vector == 'u' && position > 1) {
                  moveCursor(&cursor, vector, false);
                  moveCursor(&cursor, vector, false);
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
char getCursorGameMode(void)
{
    Window window = createWindow(40, 20);

    Window menu = createField(window, 11, 6, 14, 6);

    Window yes_no = createField(menu, 0, 3, 1, 3);

    sprintf(menu.field[0],   "choose gamemode");

    sprintf(menu.field[3], ">  with machine");
    sprintf(menu.field[5], ">  with human  ");

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
                  moveCursor(&cursor, vector, false);
                  moveCursor(&cursor, vector, false);
                  position++;
              }

              else if (vector == 'u' && position > 1) {
                  moveCursor(&cursor, vector, false);
                  moveCursor(&cursor, vector, false);
                  position--;
              }
              vector = '\0';

              break;

           case '\n':
              if (position == 1) {
                  freeCursor(cursor);
                  return 'm';
              }
              else {
                  freeCursor(cursor);
                  return 'p';
              }
           
               break;
        }

        renderWindow(window, 0);
    }

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

    srand(time(NULL));

    bool hide_ships = true;

    updateShipsField(window.ships_field, player_2 -> field, hide_ships);
    updateShipsLeft(window.ships_left, player_2 -> ships_left);
    
    while (!isWin(player_2 -> ships)) {

           char move[NAME_LENGTH + strlen(" move")];
           sprintf(move, "%s move", player_1 -> name);
           printToTextField(window.text_field, move, 'W');

           renderWindow(window.root, RENDER_OPT);

           int* shot;
           if (player_1 -> is_machine)
                shot = getShotAtPlayer(*player_2, window, 'a');
           else
                shot = getShotAtPlayer(*player_2, window, 'c');


           if (player_2 -> field[shot[1]][shot[0]].is_hitted)
               continue;

           player_2 -> field[shot[1]][shot[0]].is_hitted = true;
            
           if (isHit (shot, player_2 -> field)) {

               player_1 -> count++;

               int shipId = getShipId(shot, player_2 -> field);

               printToTextField(window.text_field, "HITTED", 'R');  

               Animation boom = createBoomAnimation(shot[0], shot[1]);
               renderAnimationOnWindow(boom, window.game_field, window.root);

               if (isKilled(shipId, player_2 -> ships)) {

                   Ship ship = player_2 -> ships[shipId];

                   if (ship.size != 1) {
                        Animation* animations = NULL;
                        int* size;
 
                        for (int i = 0; i < ship.size; i++) {
                           Animation tmp = createBoomAnimation(ship.cells[i] -> x, ship.cells[i] -> y);
                           size = addAnimation(&animations, tmp);
                        }

                        int frames = animations[0].frames;

                        for (int i = 0; i <= frames; i++) {
                            renderAnimationArrayOnWindow(animations, window.game_field, size, 's');
                            renderWindow(window.root, 0); 
                            usleep(animations[0].ms);
                        }

                        free(animations);
                        *size = 0;
                    }

                    player_2 -> ships[shipId].is_killed = true;

                    setEnvire(player_2 -> ships[shipId], player_2 -> field);

                    delete(player_2 -> ships[shipId], player_2 -> ships_left);

                    updateShipsLeft(window.ships_left, player_2 -> ships_left);

                    printToTextField(window.text_field, "KILLED", 'R'); 
               }
               
               updateShipsField(window.ships_field, player_2 -> field, true);

               renderWindow(window.root, RENDER_OPT);

               usleep(SLEEP_TIME);

               continue;

           }

           printToTextField(window.text_field, "MISSED", 'C');

           Animation splash = createSplashAnimation(shot[0], shot[1]);
           renderAnimationOnWindow(splash, window.game_field, window.root);

           updateShipsField(window.ships_field, player_2 -> field, true);
           renderWindow(window.root, RENDER_OPT);

           usleep(SLEEP_TIME);

           break;
    
       }

}

int* getShotAtPlayer(Player player, GameWindow window, char shotMode) 
{
    int* shot;
    if (shotMode == 'a')
        shot = getMachineShot(player);
    else {
        shot = getCursorShot(window);
    }
    
    return shot;

}

int* getCursorShot(GameWindow window)
{

    static int shot[2];

    Cursor cursor;

    initCursorOnWindow(&cursor, window.ships_field, 'm', 'R', 1, 1);
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
                vector = '\0';
                recoverStoredArea(cursor);
                freeCursor(cursor);
                return shot;
                break;

            default:
                vector = '\0';
        
        } 
        if (vector != '\0')
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


void getPlayerName(Player* player)
{
    static int count = 0;

    system("clear");

    if (player -> is_machine) {
        strcpy(player -> name, "Jasper");
        system("clear");
        return;
    }

    if (count == 0) {
        printf("\n\n\n\n\n\n\n\n\n\n\033[2m                        Player name #1: ");
    }
    else {
        printf("\n\n\n\n\n\n\n\n\n\n\033[2m                        Player name #2: ");
    }

    fgets(player -> name, NAME_LENGTH, stdin);

    player -> name[strlen(player -> name) - 1] = '\0';

    printf("\033[0m");
    system("clear");

    count++;

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

bool isWin (Ship* ships) {

    int count = 0;

    for (int i = 0; i < 10; i++)
        if (ships[i].is_killed)
            count++;

    if (count == 10)
        return true;

    else
        return false;

}

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

int* createSetArea(Ship ship)
{
    static int setArea[4];

    setArea[0] = ship.cells[0] -> x - 1;
    setArea[1] = ship.cells[0] -> y - 1;
    setArea[2] = ship.cells[ship.size - 1] -> x + 1;
    setArea[3] = ship.cells[ship.size - 1] -> y + 1;

    return setArea;

}

