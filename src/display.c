#include <stdio.h>
#include "display.h"

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
