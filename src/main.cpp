#include <hybrid_Astar.hpp>
#include <iostream>
#include <map.hpp>
#include <utility>
#include <vector>

std::vector<std::vector<int>> random_Num_map(int row, int col);

int main() {
  std::vector<std::vector<int>> map = random_Num_map(70, 125);

  std::pair<int, int> begin(0, 0), end(60, 115);
  // std::pair<int, int> begin(11, 0), end(11, 5);

  Map my_map(map);
  my_map.NumtoState();

  std::vector<std::vector<State>> my_Statemap = my_map.getmap_State();
  HybridAstar my_Astar(my_Statemap);

  std::vector<std::pair<int, int>> my_path = my_Astar.getpath(begin, end);

  my_map.updatePath(my_path);
  if (my_path.empty())
    std::cout << "path empty" << std::endl;

  my_map.State_change(begin, BEGIN);
  my_map.State_change(end, END);
  my_map.show();

  return 0;
}

std::vector<std::vector<int>> random_Num_map(int row, int col) {
  std::vector<std::vector<int>> array(row, std::vector<int>(col));

  int empty_rate = 7;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      int num = rand() % empty_rate;
      if (num == 0)
        array[i][j] = 1;
      else
        array[i][j] = 0;
    }
  }
  return array;
}
