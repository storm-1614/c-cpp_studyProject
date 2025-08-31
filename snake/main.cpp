#include <ncurses.h>
#include "src/SnakeGame.hpp"


int main (int argc, char *argv[]) {
    initscr();
    SnakeGame game;
    endwin();
    return 0;
}
