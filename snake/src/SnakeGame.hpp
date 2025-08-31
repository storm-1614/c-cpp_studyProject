#pragma once
#include <ncurses.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>

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
    void processInput() {
        chtype key = gameboard.getInput();
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

        SnakePiece next = snake.SnakePieceNext();

        if (apple != NULL) {
            switch (gameboard.getChAt(next.getY(), next.getX())) {
                case 'A':
                    delete apple;
                    apple = NULL;
                    snake.addNewHead(next);
                    gameboard.add(snake.head());

                    break;

                case ' ': {
                    snake.addNewHead(next);
                    gameboard.add(snake.head());

                    Empty replace(snake.tail().getY(), snake.tail().getX());
                    gameboard.add(replace);
                    snake.removeOldTail();
                    break;
                }
                default:
                    game_over = true;
                    break;
            }
        }
        if (apple == NULL) {
            int y, x;
            gameboard.getEmptyCoordinate(y, x);
            apple = new Apple(y, x);
            gameboard.add(*apple);
        }
    }

    // Redraw Window
    void redraw() { gameboard.redraw(); }

    void initall() {
        snake.addNewHead(SnakePiece(2, 2));
        gameboard.add(snake.head());

        snake.addNewHead(snake.SnakePieceNext());
        gameboard.add(snake.head());

        snake.setDirection(down);
        snake.addNewHead(snake.SnakePieceNext());
        gameboard.add(snake.head());

        int y, x;
        gameboard.getEmptyCoordinate(y, x);
        apple = new Apple(y, x);
        gameboard.add(*apple);
    }

   public:
    // Game loop;
    SnakeGame() {
        srand(time(NULL));
        int size = 10;
        // draw window
        gameboard = Board(size, size * 2);

        initall();

        while (!game_over) {
            processInput();
            updateState();
            redraw();
            gameboard.sleep();
        }
    }
    ~SnakeGame() { delete apple; }
};
