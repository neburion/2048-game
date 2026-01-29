#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "display.h"

void drawBox(int x, int y, int width, int height){
    for(int i = x; i <= x+width; i++){
        for(int j = y; j <= y+height; j++){
            // corners
            if(i == x && j == y){
                mvwprintw(stdscr, j, i, "*");
            } else if(i == x && j == y+height){
                mvwprintw(stdscr, j, i, "*");
            } else if(i == x+width && j == y){
                mvwprintw(stdscr, j, i, "*");
            } else if(i == x+width && j == y+height){
                mvwprintw(stdscr, j, i, "*");
            }

            // sides
            else if(i == x || i == x+width){
                mvwprintw(stdscr, j, i, "|");
            } else if(j == y || j == y+height){
                mvwprintw(stdscr, j, i, "-");
            }
        }
    }
}

void drawMenu(int x, int y, int width, char **title, int titleLen, char ***content, int contentSize){
    int height = contentSize+1;
    char *t = *title;
    char **c = *content;

    drawBox(x, y, width, height);
    mvwprintw(stdscr, y, (x+width/2)-(titleLen/2), "%s", t);

    for(int i = 0; i < contentSize; i++){
        mvwprintw(stdscr, y+1+i, x+2, "%s", c[i]);
    }

    refresh();
}

void drawScore(int score){
    int width = 11;
    int x = (WIN_WIDTH/2)-(width/2);
    int y = 0;
    char *n = "-SCORE:";
    int nLen = 6;
    char **s = malloc(sizeof(char*));
    s[0] = malloc(width*sizeof(char));
    sprintf(s[0], "%d", score);

    drawMenu(x-1, y, width, &n, nLen, &s, 1);

    free(s[0]);
    free(s);
}

void drawControls(char ***controls, int controlNum){
    int width = 22;
    int x = 0;
    int y = (WIN_HEIGHT/2)-controlNum+1;
    char *n = "CONTROLS:";
    int nLen = 9;
    char **c = *controls;

    drawMenu(x, y, width, &n, nLen, &c, controlNum);
}

void drawGame(int ***grid){
    int width = (GAME_RESOLUTION*5);
    int height = (GAME_RESOLUTION*2);
    int x = (WIN_WIDTH/2)-(width/2);
    int y = (WIN_HEIGHT/2)-(height/2);
    int **g = *grid;

    drawBox(x, y, width, height);
    for (int i = 0; i < GAME_RESOLUTION; i++){
        for (int j = 0; j < GAME_RESOLUTION; j++){
            if (g[j][i] == 0) {
                mvwprintw(stdscr, y+(j*2)+1, x+(i*5)+1, "    |");
            } else {
                mvwprintw(stdscr, y+(j*2)+1, x+(i*5)+1, "%.4d|", g[j][i]);
            }
            mvwprintw(stdscr, y+(j*2)+2, x+(i*5)+1, "-----");
        }
    }

    refresh();
}

void gameOver(char state){
    char *message;
    int messageLen;

    char *qMessage = "Press \"Q\" to quit the game.";
    int qMessageLen = 27;

    if(state == 'w'){
        message = "You won!";
        messageLen = 8;
    } else {
        message = "You lost.";
        messageLen = 9;
    }

    int x = (WIN_WIDTH/2)-(messageLen/2);
    int y = WIN_HEIGHT/2;
    int qX = (WIN_WIDTH/2)-(qMessageLen/2);
    int qY = y+1;

    clear();
    mvwprintw(stdscr, y, x, "%s", message);
    mvwprintw(stdscr, qY, qX, "%s", qMessage);
    refresh();
}
