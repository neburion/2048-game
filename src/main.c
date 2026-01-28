#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "logic.h"
#include "input.h"


int main(){
    srand(time(NULL)); // rand() seed
    char input; // input input holder
    bool endFlag = false;
    atexit(disableRawMode);
    at_quick_exit(disableRawMode);

    // setup the game
    int **grid = setup();
    newTile(&grid);
    displayer(&grid);
    enableRawMode();

    // game loop
    while (1){
        input = getInput();
        swipe(&grid, input);
        newTile(&grid);
        displayer(&grid);

        switch(check(&grid)){
          case 'n':
            break;
          case 'l':
            printf("You lose.\n");
            endFlag = true;
            break;
          case 'w':
            printf("You win!\n");
            endFlag = true;
            break;
        }
        if(endFlag){
            break;
        }
    }

    disableRawMode();

    // free malloc
    for (int i = 0; i < GAME_RESOLUTION; i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}
