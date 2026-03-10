

#include <iostream>
#include <vector>

int main() {
  std::vector<std::vector<int>> matrix(4, std::vector<int>(4, 0));
  std::vector<std::vector<int>> res(4, std::vector<int>(4, 0));
  int first = 1, step = 2;
  int count = first;
  int max, min, sum;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = count;
      count += step;
    }
  }
  res = matrix;
  max = count, min = first;
  sum = max + min;

  for (int i = 0; i < 4; i++)
    res[i][i] = 32 - res[i][i];
  for (int i = 0; i < 4; i++)
    res[i][3 - i] = 32 - res[i][3 - i];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << res[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  return 0;
}
