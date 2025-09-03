#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class Board {
   private:
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

   public:
    Board() { srand(time(NULL)); }

    int size = board.size();

    void showBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << board.at(i).at(j) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "ee";
    }

    void randNum() {
        int x, y;
        while (board[x = rand() % size][y = rand() % size] != 0);
        board[x][y] = 2;
    }

    void moveLeft() {
        std::cout << "eeee";
        for (int i = 0; i < size; i++) {
            // 创建新列表
            std::vector<int> row;
            // 移除该行所有空格
            for (int j = 0; j < size; j++) {
                if (board[i][j] != 0) {
                    row.emplace_back(board[i][j]);
                }
                // 合并操作
                for (int j = 0; j < row.size() - 1; j++) {
                    if (row[j] == row[j + 1]) {
                        row[j] *= 2;
                        row[j + 1] = 0;
                        j++;
                    }
                }

                // 移除合并产生的空格
                std::vector<int> newRow;
                for (int j = 0; j < row.size(); j++) {
                    if (row[j] != 0) {
                        newRow.emplace_back(row[j]);
                    }
                }

                // 填充空格
                while (newRow.size() < size) {
                    newRow.emplace_back(0);
                }

                // 更新棋盘
                for (int j = 0; j < size; j++) {
                    board[i][j] = newRow[j];
                }
            }
        }
    }
};
