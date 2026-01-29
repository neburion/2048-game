#ifndef LOGIC_H_
#define LOGIC_H_

int score;

void fill(int ***grid, int x, int y, int value);
void newTile(int ***grid);
int **setup();
int swipe(int ***grid, char input, int curScore);
char check(int ***grid);

#endif
