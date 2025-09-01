#pragma once
#include <ncurses.h>

#include <cstdlib>

#include "Drawable.hpp"

class Board {
   private:
    WINDOW *board_win;
    int y, x, col, row;

   public:
    Board(int height, int weigh) {
        getmaxyx(stdscr, y, x);
        y *= 0.25;
        x *= 0.25;
        this->col = height;
        this->row = weigh;
        initialize();
    }
    Board() {}

    //initialize window, config window.
    void initialize() {

        board_win = newwin(col, row, y, x);
        keypad(board_win, true);
        nodelay(board_win, true);
        noecho();
        curs_set(0);
        clear();
    }

    //clear window and redraw boarder.
    void clear() {
        wclear(board_win);
        box(board_win, 0, 0);
    }

    void redraw() { wrefresh(board_win); }

    //add element, use class Drawable.
    void add(Drawable piece) {
        mvwaddch(board_win, piece.getY(), piece.getX(), piece.getIcon());
    }

    chtype getInput() { return wgetch(board_win); }

    int getX() { return x; }

    int getY() { return y; }

    //use random number find blank character, if is blank, stop loop;
    void getEmptyCoordinate(int &y, int &x) {
        while (mvwinch(board_win, y = rand() % col, x = rand() % row) != ' ');
    }

    // Get coordinate character.
    int getChAt(int y, int x) { return mvwinch(board_win, y, x); }

    //sleep board_win.
    void sleep(int time) { wtimeout(board_win, time); }

    void gameOver(int score){
        clear();
        redraw();
        mvwprintw(board_win, 1, 1, "GameOver!");
        mvwprintw(board_win, 2, 1, "Score: %d", score);
        wgetch(board_win);
    }
};
