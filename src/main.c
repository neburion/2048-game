#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"
#include "logic.h"

int main(){
    srand(time(NULL)); // rand() seed
    char input; // input input holder
    char state;

    // setup ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    clear();

    // setup the game
    int **grid = setup();
    newTile(&grid);

    // controls
    int controlNum = 5;
    char **controls = malloc(controlNum * sizeof(char*));
    for(int i = 0; i < controlNum; i++){
        controls[i] = malloc(sizeof(char)*20);
    }
    strcpy(controls[0], "Quit: q");
    strcpy(controls[1], "Up: arrow-up");
    strcpy(controls[2], "Down: arrow-down");
    strcpy(controls[3], "Right: arrow-right");
    strcpy(controls[4], "Left: arrow-left");

    drawScore(99999999);
    drawControls(&controls, controlNum);
    drawGame(&grid);

    // game loop
    while (1){
        input = getch();
        if(input != 'q'){
            swipe(&grid, input);
        }
        newTile(&grid);
        drawGame(&grid);

        state = check(&grid);
        if(input == 'q' || state != 'n'){
            break;
        }
    }

    // on game over
    gameOver(state);
    while(input != 'q'){
        input = getch();
    }

    endwin(); // close ncurses

    // free malloc
    for (int i = 0; i < GAME_RESOLUTION; i++){
        free(grid[i]);
    }
    free(grid);
    for(int i = 0; i < controlNum; i++){
        free(controls[i]);
    }
    free(controls);

    return 0;
}
