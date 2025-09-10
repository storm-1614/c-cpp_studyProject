#include <ncurses.h>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

class Board {
   private:
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    void transposeMatrix() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                std::swap(board[i][j], board[j][i]);
            }
        }
    }

   public:
    Board() { srand(time(NULL)); }

    int size = board.size();

    void showBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printw("%d\t", board[i][j]);
            }
            printw("\n");
        }
    }

    void randNum() {
        int x, y;
        std::pair<int, int> coordinate;
        std::vector<std::pair<int, int>> voidList;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == 0) voidList.emplace_back(i, j);
            }
        }

        if (!voidList.empty()) {
            coordinate = voidList[rand() % voidList.size()];

            x = coordinate.first;
            y = coordinate.second;

            board[x][y] = 2;
        }
    }

    void moveLeft() {
        for (int i = 0; i < size; i++) {
            // 创建新列表
            std::vector<int> row;
            // 移除该行所有空格
            for (int j = 0; j < size; j++) {
                if (board[i][j] != 0) {
                    row.emplace_back(board[i][j]);
                }
            }
            // 合并操作
            for (int j = 0; j < (int)row.size() - 1; j++) {
                if (row[j] == row[j + 1]) {
                    row[j] *= 2;
                    row[j + 1] = 0;
                    j++;
                }
            }

            std::vector<int> newRow;
            for (int j = 0; j < (int)row.size(); j++) {
                if (row[j] != 0) {
                    newRow.emplace_back(row[j]);
                }
            }

            // 填充空格
            while ((int)newRow.size() < size) {
                newRow.emplace_back(0);
            }

            // 更新棋盘
            for (int j = 0; j < size; j++) {
                board[i][j] = newRow[j];
            }
        }
    }

    void moveRight() {
        for (int i = 0; i < size; i++) {
            std::reverse(board.at(i).begin(), board.at(i).end());
        }

        moveLeft();

        for (int i = 0; i < size; i++) {
            std::reverse(board.at(i).begin(), board.at(i).end());
        }
    }

    void moveUp() {
        transposeMatrix();
        moveLeft();
        transposeMatrix();
    }

    void moveDown() {
        transposeMatrix();
        moveRight();
        transposeMatrix();
    }
};
