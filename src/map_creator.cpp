#include "map_creator.hpp"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

std::vector<std::vector<int>> random_Num_map(int row, int col) {
  std::vector<std::vector<int>> array(row, std::vector<int>(col));

  int empty_rate = 6;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      int num = (rand() % empty_rate);
      if (num == 0)
        array[i][j] = 1;
      else
        array[i][j] = 0;
    }
  }
  return array;
}

std::vector<std::vector<int>> regular_Num_map(int row, int col,
                                              int object_size) {
  std::vector<std::vector<int>> array(row, std::vector<int>(col, 1));

  std::vector<std::pair<int, int>> direction = {
      {object_size, 0}, {-object_size, 0}, {0, object_size}, {0, -object_size}};

  std::pair<int, int> current = {row / 2, col / 2};

  int time = 250;
  for (int m = 0; m < 250; m++) {
    int run_1 = rand() % 10;

    for (int t = 0; t < time; t++) {
      int run = (rand() + run_1) % 4;
      std::cout << current.first << "|" << current.second << std::endl;
      std::cout << "." << std::endl;

      if (current.first < 0 || current.first >= row || current.second < 0 ||
          current.second >= col) {
        std::cout << "over" << std::endl;
        break;
      }

      for (int i = 0; i < object_size; i++) {
        for (int j = 0; j < object_size; j++) {
          array[current.first + i][current.second + j] = 0;
        }
      }

      current.first = current.first + direction[run].first;
      current.second = current.second + direction[run].second;

      std::cout << current.first << "|" << current.second << std::endl;
      std::cout << ".." << std::endl;
    }
  }
  return array;
}