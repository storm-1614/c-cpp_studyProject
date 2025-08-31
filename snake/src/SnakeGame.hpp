#pragma once
#include <ncurses.h>
#include <unistd.h>

#include "Apple.hpp"
#include "Board.hpp"
#include "Empty.hpp"
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
    void processInput(chtype key) {
        switch (key) {
            case 'w':
            case KEY_UP:
                snake.setDirection(up);
                break;
            case 'a':
            case KEY_LEFT:
                snake.setDirection(left);
                break;
            case 's':
            case KEY_DOWN:
                snake.setDirection(down);
                break;
            case 'd':
            case KEY_RIGHT:
                snake.setDirection(right);
            default:
                break;
        }
    }

    // Update element.
    void updateState() {
        gameboard.redraw();
        apple = new Apple(8, 10);
        gameboard.add(*apple);

        snake.addNewHead(snake.SnakePieceNext());
        gameboard.add(snake.head());

        Empty replace(snake.tail().getY(), snake.tail().getX());
        gameboard.add(replace);
        snake.removeOldTail();
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
            processInput(gameboard.getInput());
            updateState();
            redraw();
            sleep(1);
        }
    }
    ~SnakeGame() {}
};
