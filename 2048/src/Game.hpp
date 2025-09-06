#include <ncurses.h>


#include "Board.hpp"

class Game {
   private:
    bool gameOver = false;
    Board board;

   public:
    Game() {
        initscr();
        noecho();
        while (!gameOver) {
            clear();
            board.randNum();
            board.showBoard();
            getInput();
            refresh();
        }

        getch();
        endwin();
    }

    void getInput() {
        chtype key = getch();
        switch (key) {
            case 'w':
                board.moveUp();
                break;
            case 'a':
                board.moveLeft();
                break;
            case 's':
                board.moveDown();
                break;
            case 'd':
                board.moveRight();
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
};
