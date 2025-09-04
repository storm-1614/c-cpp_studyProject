#include <iostream>
#include <ncurses.h>

#include "Board.hpp"

class Game{
    private:
        bool gameOver = false;
        Board board;

    public:
    Game(){
        board.randNum();
        board.showBoard();
        board.moveDown();
        std::cout << "============\n";
        board.showBoard();
    }
};

