#pragma once
#include <ncurses.h>

class ScoreBoard {
   private:
    WINDOW* scoreBoard;

   public:
    ScoreBoard(int x, int y, int width, int initScore) {
        scoreBoard = newwin(1, width, y, x);
        refreshScore(initScore);
    }

    void redraw() { wrefresh(scoreBoard); }

    void refreshScore(int score) {
        wclear(scoreBoard);
        wprintw(scoreBoard, "Score:%d", score);
    }

    ScoreBoard() {}
};
