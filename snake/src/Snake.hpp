#pragma once

#include <ncurses.h>

#include <queue>

#include "Drawable.hpp"

enum Directon { up = -1, down = 1, left = -2, right = 2 };

// Every Picec of a snake
class SnakePiece : Drawable {
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

    // Get current direction;

    void addNewHead(SnakePiece piece) { body.emplace(piece); }

    void removeOldTail() { body.pop(); }

    chtype getCurrentDirection(Directon newDirection) { return direction; }
    void setDirection(Directon newDirection) {
        if (newDirection + direction != 0) direction = newDirection;
    }

    SnakePiece tead() { return body.back(); }

    SnakePiece tail() { return body.front(); }
};
