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
    int score = 0;

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
    char up = 'k';
    char down = 'j';
    char right = 'l';
    char left = 'h';

    int controlNum = 5;
    char **controls = malloc(controlNum * sizeof(char*));
    for(int i = 0; i < controlNum; i++){
        controls[i] = malloc(sizeof(char)*20);
    }
    strcpy(controls[0], "Quit: q");
    strcpy(controls[1], "Up: k");
    strcpy(controls[2], "Down: j");
    strcpy(controls[3], "Right: l");
    strcpy(controls[4], "Left: h");

    drawScore(0);
    drawControls(&controls, controlNum);
    drawGame(&grid);

    // game loop
    while (1){
        input = getch();
        if(input == up || input == down || input == right || input == left){
            score = swipe(&grid, input, score);
            newTile(&grid);
        }
        drawScore(score);
        drawGame(&grid);

        state = check(&grid);
        if(input == 'q' || state != 'n'){
            break;
        }
    }

    // on game over
    gameOver(state, score);
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
