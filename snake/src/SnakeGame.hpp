#pragma once
#include "Board.hpp"

class SnakeGame {
   private:
    bool game_over = false;
    Board gameboard;

   private:
    void processInput(){
        
    }
    void updateState(){
        gameboard.redraw();
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
