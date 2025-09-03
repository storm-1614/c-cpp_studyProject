#include "Board.hpp"

class Game{
    private:
        bool gameOver = false;
        Board board;

    public:
    Game(){
        board.randNum();
        board.showBoard();
        std::cout << "eeee";
        board.moveLeft();
        board.showBoard();
    }
};

