#pragma once
#include <ncurses.h>

#include "Apple.hpp"
#include "Board.hpp"
#include "Snake.hpp"

class SnakeGame {
   private:
    bool game_over = false;
    Board gameboard;
    Snake snake;
    Apple* apple;

   private:
    // Process event from keyboard.
    // Such as change direction, pause game, exit game;
    void processInput() {}

    // Update element.
    void updateState() {
        gameboard.redraw();
        apple = new Apple(8, 10);
        gameboard.add(*apple);
    }

    // Redraw Window
    void redraw() { gameboard.redraw(); }

    void initSnake() {
        snake.addNewHead(SnakePiece(2, 2));
        gameboard.add(snake.head());

        snake.addNewHead(snake.SnakePieceNext());
        gameboard.add(snake.head());
        snake.setDirection(down);
        snake.addNewHead(snake.SnakePieceNext());
        gameboard.add(snake.head());
    }

   public:
    // Game loop;
    SnakeGame() {
        int size = 10;
        // draw window
        gameboard = Board(size, size * 2);

        initSnake();

        while (!game_over) {
            processInput();
            updateState();
            redraw();
        }
    }
    ~SnakeGame() {}
};
