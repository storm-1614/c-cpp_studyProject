#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Apple.hpp"

class SnakeGame {
   private:
    bool game_over = false;
    Board gameboard;
    Apple* apple;

   private:
    void processInput(){
        
    }
    void updateState(){
        gameboard.redraw();
        apple = new Apple(3, 5);
        gameboard.add(*apple);
        

    }
    void redraw(){}

   public:
    SnakeGame() {
        int size = 10;
        gameboard = Board(size, size * 2);

        while (!game_over) {
            processInput();
            updateState();
            redraw();
        }
    }
    ~SnakeGame(){}
};
