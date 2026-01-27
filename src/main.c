#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GAME_RESOLUTION 4

// prints the current grid to the screen
void displayer(int ***grid){
    int **g = *grid;
    int dCharLength = 19;

    printf(" ");
    for (int i = 0; i < dCharLength; i++){
        printf("_");
    }
    printf("\n");

    for (int i = 0; i < GAME_RESOLUTION; i++){
        for (int j = 0; j < GAME_RESOLUTION; j++){
            if (g[i][j] == 0) {
                printf("|%s", "Empt");
            } else {
                printf("|%.4d", g[i][j]);
            }
        }
        printf("|\n");
    }

    printf(" ");
    for (int i = 0; i < dCharLength; i++){
        printf("¯");
    }
    printf("\n");
}

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
void swipe(int ***grid, char direction){
    int **g = *grid;
    int actions;

    switch(direction){
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

int main(){
    srand(time(NULL)); // rand() seed
    char direction; // direction input holder
    bool endFlag = false;

    // setup the game
    int **grid = setup();
    newTile(&grid);
    displayer(&grid);

    // game loop
    while(1){
        scanf(" %c", &direction);
        swipe(&grid, direction);
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

    // free malloc
    for (int i = 0; i < GAME_RESOLUTION; i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}
