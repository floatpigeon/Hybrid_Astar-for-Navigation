#pragma once

#include <vector>
enum State {
  UNKNOW = 0,
  EMPTY = 1,
  OPEND = 2,
  CLOSED = 3,
  OBSTACLE = 4,
  OBJECT = 5
};

class Map {
public:
  Map(std::vector<std::vector<State>> &map) : map(map) {
    real_row = map.size();
    real_col = map[0].size();
  }

  std::vector<std::vector<State>> toGrid();

private:
  int real_row, real_col;
  int grid_size;

  std::vector<std::vector<State>> map;
};