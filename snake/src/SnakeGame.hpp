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
    const int size = 10;
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
                break;
            case 'p':
                gameboard.sleep(-1);
                // detect key, until key is p again;
                while (gameboard.getInput() == 'p') gameboard.sleep(300);
                break;

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
                case 'A': {
                    destoryApple();
                    addNewHead(next);
                    break;
                }

                case ' ': {
                    addNewHead(next);
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
        if (apple == NULL) createApple();
    }

    // Redraw Window
    void redraw() { gameboard.redraw(); }

    // initialize snake body and apple.
    void initall() {
        addNewHead(SnakePiece(2, 2));
        addNewHead(snake.SnakePieceNext());
        addNewHead(snake.SnakePieceNext());

        createApple();
    }

    // Add new head to queue and draw into board.
    void addNewHead(SnakePiece head) {
        snake.addNewHead(head);
        gameboard.add(head);
    }

    void createApple() {
        int y, x;
        gameboard.getEmptyCoordinate(y, x);
        apple = new Apple(y, x);
        gameboard.add(*apple);
    }

    void destoryApple() {
        delete apple;
        apple = NULL;
    }

   public:
    // Game loop;
    SnakeGame() {
        srand(time(NULL));
        // draw window
        gameboard = Board(size, size * 2);

        initall();

        while (!game_over) {
            processInput();
            updateState();
            redraw();
            gameboard.sleep(300);
        }
    }
    ~SnakeGame() { delete apple; }
};
