#pragma once
#include <ncurses.h>

class Drawable {
   public:
    Drawable(int y, int x, chtype ch) {
        this->x = x;
        this->y = y;
        this->icon = ch;
    }
    Drawable() {
        y = x = 0;
        icon = ' ';
    }
    int getX() { return x; }
    int getY() { return y; }

    chtype getIcon() { return icon; }

   protected:
    int x, y;
    chtype icon;
};
