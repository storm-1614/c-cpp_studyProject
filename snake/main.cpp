#include <ncurses.h>

#include "src/SnakeGame.hpp"

int main(int argc, char *argv[]) {
    initscr();
    refresh();
    SnakeGame game;
    getch();
    endwin();
    return 0;
}
