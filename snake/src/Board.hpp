#pragma once
#include <ncurses.h>

#include "Drawable.hpp"

class Board {
   private:
    WINDOW* board_win;
    int y, x, col, row;

   public:
    Board(int height, int weigh) {
        nodelay(board_win, true);
        this->col = height;
        this->row = weigh;
        initialize();
    }
    Board() {}

    void initialize() {
        keypad(board_win, true);
        noecho();
        nodelay(board_win, true);
        curs_set(0);
        getmaxyx(stdscr, y, x);
        y *= 0.25;
        x *= 0.25;
        board_win = newwin(col, row, y, x);
        clear();
    }

    void clear() {
        wclear(board_win);
        box(board_win, 0, 0);
    }

    void redraw() { wrefresh(board_win); }

    void add(Drawable piece) {
        mvwaddch(board_win, piece.getY(), piece.getX(), piece.getIcon());
    }

    chtype getInput() { 
        return wgetch(board_win);
    }
    void sleep() { wtimeout(board_win, 300); }
};
