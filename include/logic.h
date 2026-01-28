#ifndef LOGIC_H_
#define LOGIC_H_

void fill(int ***grid, int x, int y, int value);
void newTile(int ***grid);
int **setup();
void swipe(int ***grid, char input);
char check(int ***grid);

#endif
