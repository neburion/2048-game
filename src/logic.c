#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "display.h"

// fills a tile
void fill(int ***grid, int x, int y, int value){
    int **g = *grid;
    g[x][y] = value;
}

// adds a new tile at a empty random position
void newTile(int ***grid){
    int **g = *grid;
    int x = rand()%GAME_RESOLUTION;
    int y = rand()%GAME_RESOLUTION;
    while (g[x][y] != 0) {
        x = rand()%GAME_RESOLUTION;
        y = rand()%GAME_RESOLUTION;
    }
    if (rand()%9 == 1) {
        g[x][y] = 4;
        return;
    }
    g[x][y] = 2;
}

// setup the grid
int **setup(){
    int **grid = malloc(sizeof(int*) * GAME_RESOLUTION);
    for (int i = 0; i < GAME_RESOLUTION; i++){
        grid[i] = malloc(sizeof(int) * GAME_RESOLUTION);
    }
    for (int i = 0; i < GAME_RESOLUTION; i++){
        for (int j = 0; j < GAME_RESOLUTION; j++){
            grid[i][j] = 0;
        }
    }
    return grid;
}

// handles swiping the grid
void swipe(int ***grid, char input){
    int **g = *grid;
    int actions;

    switch(input){
      case 'k':
        while (1) {
            actions = 0;
            for(int i = 1; i < GAME_RESOLUTION; i++){
                for(int j = 0; j < GAME_RESOLUTION; j++){
                    if(!(g[i][j] == 0 && g[i-1][j] == 0)){
                        if(g[i][j] == g[i-1][j] || g[i-1][j] == 0){
                            fill(grid, i-1, j, (g[i][j] + g[i-1][j]));
                            fill(grid, i, j, 0);
                            actions++;
                        }
                    }
                }
            }
            if(actions == 0){
                break;
            }
        }
        break;
      case 'j':
        while (1) {
            actions = 0;
            for(int i = GAME_RESOLUTION-2; i >= 0; i--){
                for(int j = 0; j < GAME_RESOLUTION; j++){
                    if(!(g[i][j] == 0 && g[i+1][j] == 0)){
                        if(g[i][j] == g[i+1][j] || g[i+1][j] == 0){
                            fill(grid, i+1, j, (g[i][j] + g[i+1][j]));
                            fill(grid, i, j, 0);
                            actions++;
                        }
                    }
                }
            }
            if(actions == 0){
                break;
            }
        }
        break;
      case 'l':
        while (1) {
            actions = 0;
            for(int i = 0; i < GAME_RESOLUTION; i++){
                for(int j = GAME_RESOLUTION-2; j >= 0; j--){
                    if(!(g[i][j] == 0 && g[i][j+1] == 0)){
                        if(g[i][j] == g[i][j+1] || g[i][j+1] == 0){
                            fill(grid, i, j+1, (g[i][j] + g[i][j+1]));
                            fill(grid, i, j, 0);
                            actions++;
                        }
                    }
                }
            }
            if(actions == 0){
                break;
            }
        }
        break;
      case 'h':
        while (1) {
            actions = 0;
            for(int i = 0; i < GAME_RESOLUTION; i++){
                for(int j = 1; j < GAME_RESOLUTION; j++){
                    if(!(g[i][j] == 0 && g[i][j-1] == 0)){
                        if(g[i][j] == g[i][j-1] || g[i][j-1] == 0){
                            fill(grid, i, j-1, (g[i][j] + g[i][j-1]));
                            fill(grid, i, j, 0);
                            actions++;
                        }
                    }
                }
            }
            if(actions == 0){
                break;
            }
        }
        break;
      default:
        printf("Error! Incorrect character was give to swipe()!");
        return;
    }
}

// checks if the game ended
char check(int ***grid){
    int **g = *grid;
    bool loseFlag = true;
    for(int i = 0; i < GAME_RESOLUTION; i++){
        for(int j = 0; j < GAME_RESOLUTION; j++){
            if(g[i][j] == 2048){
                return 'w';
            }
            if(g[i][j] == 0){
                loseFlag = false;
            }
        }
    }
    if(loseFlag){
        return 'l';
    }
    return 'n';
}
