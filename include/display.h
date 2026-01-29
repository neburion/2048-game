#ifndef DISPLAY_H_
#define DISPLAY_H_

#define GAME_RESOLUTION 4
#define WIN_WIDTH COLS
#define WIN_HEIGHT LINES

void drawScore(int score);
void drawControls(char ***controls, int controlNum);
void drawGame(int ***grid);
void gameOver(char state);

#endif
