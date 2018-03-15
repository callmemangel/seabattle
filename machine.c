#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "ships.h"
#include "time.h"


int getMachineLvl(void)
{
    int lvl;

    printf("Choose lvl of hardness\n"
            "0 - eazy\n"
            "1 - middle\n" );

    do {

        lvl = getchar() - '0';
        if (lvl != '\n')
            clearInputBuff();

    } while (lvl != 0 && lvl != 1 && lvl != 2);

    return lvl;
}


int* getMachineShot(Player player)
{

    static int machineLvl = -1;

    if (machineLvl == -1)
        machineLvl = getMachineLvl();

    int* shot;

    if (machineLvl == 0)
        shot = getEazyShot();
    else 
        shot = getMidShot(player);

    return shot;
}

int* getEazyShot()
{
    static int shot[2];
    
    int x = rand() % 10;
    int y = rand() % 10;

    shot[0] = x;
    shot[1] = y;

    return shot;
}

int* getMidShot(Player player)
{
    static int prev_shot[2] = {-2, -2};
    static int hits = 0;
    static char vector = '\0';
    static int mode = 0;

    static int curr_shot[2];


    if (prev_shot[0] == -2)
    {
        int* tmp;
        tmp = getEazyShot(); 
        curr_shot[0] = tmp[0];
        curr_shot[1] = tmp[1];

        FILE* log_file = fopen("log.txt", "a");
        fprintf(log_file, "got eazy shot with coords (%i, %i)\n", curr_shot[0], curr_shot[1]);
        fclose(log_file);


    }

    else if (vector == '\0') {
    
       vector = getRandVector(prev_shot);
       getShotForVector(prev_shot, curr_shot, vector);

       FILE* log_file = fopen("log.txt", "a");
       fprintf(log_file, "got random vector %c\n", vector);
       fprintf(log_file, "got shot for random vector %c (%i, %i)\n", vector, curr_shot[0], curr_shot[1]);
       fclose(log_file);

       vector = '\0';
 
    }

    else {

       FILE* log_file = fopen("log.txt", "a");
       while (true) {
           getShotForVector(prev_shot, curr_shot, vector); 

           if (!validCoords(curr_shot, 2)) {
               fprintf(log_file, "Wrong shot, switching\n");
               vector = switchVector(vector); 
               fprintf(log_file, "New vector = %c\n", vector);
               mode = 1;
               continue;
           }

           break;
       }
       
       fprintf(log_file, "got shot for vector %c (%i, %i)\n", vector, curr_shot[0], curr_shot[1]);
       fclose(log_file);
 
    }

    FILE* log_file = fopen("log.txt", "a");

    if (isHit(curr_shot, player.field) && !player.field[curr_shot[1]][curr_shot[0]].is_hitted) {
       fprintf(log_file, "hitted\n");
 
        hits++;
        fprintf(log_file, "hits = %i\n", hits);
        int ship_id = getShipId(curr_shot, player.field);
        fprintf(log_file, "got ship id %i\n", ship_id);

        if (hits == player.ships[ship_id].size) {
            fprintf(log_file, "SHIP KILLED\n");
            vector = '\0';
            prev_shot[0] = -2;
            prev_shot[1] = -2; 
            mode = 0;
            hits = 0;
            fclose(log_file);
            return curr_shot;
        }

        if(prev_shot[0] != -2) {
            vector = calcHitVector(prev_shot, curr_shot);
            fprintf(log_file, "CALLCULATED VECTOR %c\n", vector);
        } 

        prev_shot[0] = curr_shot[0];
        prev_shot[1] = curr_shot[1];
        fprintf(log_file, "prev_shot [0] = \n", prev_shot[0]);
        fprintf(log_file, "prev_shot [1] = \n", prev_shot[1]);
    
    }

    else if (vector != '\0' && mode == 0) {
        vector = switchVector(vector);  
        fprintf(log_file, "swithed for vector %c\n", vector);
        mode = 1;
    }

    else if (mode == 1) {
        prev_shot[0] = curr_shot[0];
        prev_shot[1] = curr_shot[1]; 
        fprintf(log_file, "prev_shot [0] = \n", prev_shot[0]);
        fprintf(log_file, "prev_shot [1] = \n", prev_shot[1]);
    }
    fclose(log_file);

    return curr_shot;
}


char getRandVector(const int* shot)
{
    char vectors[] = {'r', 'd', 'l', 'u'};
    char vector; 
    int new_shot[2];
    do {
        int rand_num = rand() % 4;
        vector = vectors[rand_num];

        getShotForVector(shot, new_shot, vector);
    
    } while (!validCoords(new_shot, 2));

    return vector;
}

char calcHitVector(int* prev_shot, int* curr_shot)
{
   if (prev_shot[0] == curr_shot[0]) {

       if (prev_shot[1] - curr_shot[1] == 1)
           return 'u';
   
       else if (prev_shot[1] - curr_shot[1] == -1)
           return 'd';
   }

   else if (prev_shot[1] == curr_shot[1]) {

       if (prev_shot[0] - curr_shot[0] == 1)
           return 'l';

       else if (prev_shot[0] - curr_shot[0] == -1)
           return 'r';
   }
   else
       return 'X';
    
}

char switchVector(const char prev_vector)
{

    char vector;
    switch (prev_vector) {
    
    case 'u':
        vector = 'd';
        break;
    case 'd':
        vector = 'u';
        break;
    case 'l':
        vector = 'r';
        break;
    case 'r':
        vector = 'l';
        break;    
    }

    return vector;
}


int* getShotForVector(const int* prev_shot, int* curr_shot, char vector) 
{

    switch (vector) {
            case 'u':
                curr_shot[0] = prev_shot[0];
                curr_shot[1] = prev_shot[1] - 1;
                break;

            case 'd':
                curr_shot[0] = prev_shot[0];
                curr_shot[1] = prev_shot[1] + 1;
                break;
            case 'l':
                curr_shot[0] = prev_shot[0] - 1;
                curr_shot[1] = prev_shot[1];
                break;
            case 'r':
                curr_shot[0] = prev_shot[0] + 1;
                curr_shot[1] = prev_shot[1];
                break;
        }

}


int* getMachineCoords(void)
{
    static int coords[4];

    int sizes[8] = {-3, -2, -1, 0, 0, 1, 2, 3};

    coords[0] = rand() % 10; //3 x
    coords[1] = rand() % 10; //7 y
    
    do {

        int size = sizes[rand() % 8]; 
        
        int randNum = rand() % 2;

        coords[randNum + 2] = coords[randNum] + size;

        coords[(randNum + 1) % 2 + 2] = coords[(randNum + 1) % 2];

   
    } while(!validCoords(coords, 4));

 
    rearrangeCoords(coords);

    return coords;

}


void rearrangeCoords(int coords[4])
{
    if (coords[0] == coords[2])
    {
        if (coords[1] > coords[3])
        {
            swap(&coords[1], &coords[3]);
        } 
    
    }

    if (coords[1] == coords[3])
        if (coords[0] > coords[2])
            swap(&coords[0], &coords[2]);

}


void swap(int *a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;

}
