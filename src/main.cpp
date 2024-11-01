#include "hybrid_Astar.hpp"
#include "map.hpp"
#include "map_creator.hpp"
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::vector<std::vector<int>> map = regular_Num_map(60, 120, 4);
  std::pair<int, int> begin(2, 70), end(29, 60);
  std::cout << "1" << std::endl;

  // std::vector<std::vector<int>> map = {{0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  //                                      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  //                                      {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
  //                                      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  //                                      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0}};
  // std::pair<int, int> begin(2, 1), end(4, 5);
  Map my_map(map);
  std::cout << "2" << std::endl;

  my_map.NumtoState();
  std::cout << "3" << std::endl;

  std::vector<std::vector<State>> my_Statemap = my_map.getmap_State();
  HybridAstar my_Astar(my_Statemap);
  std::vector<std::pair<int, int>> my_path = my_Astar.getpath(begin, end);
  my_map.updatePath_Statemap(my_path);

  // my_map.StatetoGrid(2);
  // std::vector<std::vector<State>> my_Gridmap = my_map.getmap_Grid();
  // HybridAstar my_Astar(my_Gridmap);
  // std::vector<std::pair<int, int>> my_path = my_Astar.getpath(begin, end);
  // my_map.updatePath_Gridmap(my_path);

  if (my_path.empty())
    std::cout << "path empty" << std::endl;

  my_map.State_change(begin, BEGIN);
  my_map.State_change(end, END);
  my_map.show();

  return 0;
}
