#pragma once
#include <ncurses.h>

class Board {
   private:
    WINDOW* board;
    int y, x, col, row;

   public:
    Board(int height, int weigh) {
        this->col = height;
        this->row = weigh;
        initialize();
    }
    Board() {}

    void initialize() {
        getmaxyx(stdscr, y, x);
        y *= 0.25;
        x *= 0.25;
        board = newwin(col, row, y, x);
        box(board, 0, 0);
    }

    void clear() { wclear(board); }

    void redraw() {
        wrefresh(board);
    }

    chtype getInput() { return wgetch(board); }
};
