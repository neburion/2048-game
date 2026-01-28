#include <unistd.h>
#include <termios.h>

struct termios original;

void enableRawMode(){
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original);
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

char getInput(){
    char input;
    if(read(STDIN_FILENO, &input, 1) == 1){
        return input;
    }
    return -1;
}
