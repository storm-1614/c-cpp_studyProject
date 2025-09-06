#include <ncurses.h>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
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

    //WARN: 后期死循环占用过大
    void randNum() {
        int x, y;
        while (board[x = rand() % size][y = rand() % size] != 0);
        board[x][y] = 2;
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
            // TODO: 为什么加一个 (int) 就解决了 code dumped?
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
