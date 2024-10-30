#include <Node.hpp>
#include <map.hpp>
#include <vector>

std::vector<std::vector<State>> Map::toGrid() {

  std::vector<std::vector<State>> gridmap(
      real_row / grid_size, std::vector<State>(real_col / grid_size, UNKNOW));

  for (int i = 0; i < real_row; i++) {
    int x = i / grid_size;
    for (int j = 0; j < real_col; j++) {
      int y = j / grid_size;
      if (gridmap[x][y] == UNKNOW) {
        if (map[i][j] == OBSTACLE)
          gridmap[x][y] = OBSTACLE;
        else
          gridmap[x][y] = EMPTY;
      }
    }
  }
  return gridmap;
}