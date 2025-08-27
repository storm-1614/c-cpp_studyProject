#include <ncurses.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

#define VOID 0
#define MAN 1
#define FOOD 2

class person {
   private:
    std::vector<std::vector<int>> map;
    int width = 6;
    int Px, Py;
    std::pair<int, int> food;
    int score = 0;
    void display() {
        clear();
        printw("Use w a s d to move man, <esc> to exit.\n");
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < width; ++y) {
                if (map[x][y] == MAN)
                    printw("P ");
                else if (map[x][y] == FOOD)
                    printw("& ");
                else
                    printw(". ");
            }
            printw("\n");
        }
        printw("score: %d", score);
        refresh();
    }
    bool moveP(int key) {
        int newX = Px;
        int newY = Py;
        switch (key) {
            case 'w':
                newX -= 1;
                break;
            case 'a':
                newY -= 1;
                break;
            case 's':
                newX += 1;
                break;
            case 'd':
                newY += 1;
                break;
            default:
                return false;
        }
        if (newX < 0 || newX >= width || newY < 0 || newY >= width) {
            return false;
        } else {
            map[Px][Py] = VOID;
            Px = newX;
            Py = newY;
            map[Px][Py] = MAN;
            return true;
        }
    }
    bool eatFood() {
        if (food.first == Px && food.second == Py) {
            score += 1;
            randFood();
            return true;
        } else
            return false;
    }
    void randFood() {
        map[food.first][food.second] = MAN;
        while (1) {
            if (food.first == Px && food.second == Py) {
                food.first = rand() % width;
                food.second = rand() % width;
            } else
                break;
        }
        map[food.first][food.second] = FOOD;
    }
    void initMap(int initX, int initY) {
        map.resize(width, std::vector<int>(width, 0));
        Px = initX;
        Py = initY;
        food.first = rand() % width;
        food.second = rand() % width;
        map[Px][Py] = MAN;
        randFood();
        display();
    }

   public:
    person() {
        int input;
        initscr();
        raw();
        noecho();
        initMap(1, 2);

        while (true) {
            display();
            int input = getch();
            if (input == 27) break;
            moveP(input);
            eatFood();
        }
    }
    ~person() { endwin(); }
};

int main(int argc, char *argv[]) {
    srand((int)time(NULL));
    person game;
    return 0;
}
