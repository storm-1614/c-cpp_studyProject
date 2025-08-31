#pragma once

#include <ncurses.h>

#include <queue>

#include "Drawable.hpp"

enum Directon { up = -1, down = 1, left = -2, right = 2 };

// Every Picec of a snake
class SnakePiece : public Drawable {
   public:
    SnakePiece() {
        this->x = 0;
        this->y = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x) {
        this->x = x;
        this->y = y;
        this->icon = '#';
    }
};

// Snake body and snake move add and die;
class Snake {
   private:
    std::queue<SnakePiece> body;
    Directon direction;

   public:
    Snake() { direction = right; }

    // Add piece into queue.
    void addNewHead(SnakePiece piece) { body.emplace(piece); }

    // Remove tail data;
    void removeOldTail() { body.pop(); }

    chtype getCurrentDirection(Directon newDirection) { return direction; }

    void setDirection(Directon newDirection) {
        if (newDirection + direction != 0) direction = newDirection;
    }

    SnakePiece head() { return body.back(); }

    SnakePiece tail() { return body.front(); }

    SnakePiece SnakePieceNext() {
        int row = head().getX();
        int col = head().getY();

        switch (direction) {
            case up:
                col--;
                break;
            case left:
                row--;
                break;
            case down:
                col++;
                break;
            case right:
                row++;
                break;
        }
        return SnakePiece(col, row);
    }
};
