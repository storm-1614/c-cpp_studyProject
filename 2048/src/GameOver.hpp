#pragma once
#include <ncurses.h>

class GameOver {
   private:
    WINDOW *over;

   public:
    GameOver() {
        over = newwin(10, 10, 10, 10);
        clear();
        printw("GameOver!");
        refresh();
        getch();
    }

};
