#include "hybrid_Astar.hpp"
#include "map.hpp"
#include "map_creator.hpp"
#include <iostream>
#include <utility>
#include <vector>

int main() {
  // std::vector<std::vector<int>> map = random_Num_map(70, 125);
  // std::pair<int, int> begin(0, 0), end(60, 115);

  // Map my_map(map);
  // my_map.NumtoState();
  // std::vector<std::vector<State>> my_Statemap = my_map.getmap_State();

  // HybridAstar my_Astar(my_Statemap);
  // std::vector<std::pair<int, int>> my_path = my_Astar.getpath(begin, end);

  // my_map.updatePath(my_path);
  // if (my_path.empty())
  //   std::cout << "path empty" << std::endl;

  // my_map.State_change(begin, BEGIN);
  // my_map.State_change(end, END);
  // my_map.show();

  std::vector<std::vector<int>> map_2 = regular_Num_map(70, 130, 3);
  std::pair<int, int> begin(3, 58), end(20, 85);

  Map map_test(map_2);
  map_test.NumtoState();
  // map_test.StatetoGrid(3);
  // std::vector<std::vector<State>> my_Statemap = map_test.getmap_Grid();

  std::vector<std::vector<State>> my_Statemap = map_test.getmap_State();
  HybridAstar my_Astar(my_Statemap);
  std::vector<std::pair<int, int>> my_path = my_Astar.getpath(begin, end);

  map_test.updatePath(my_path);
  if (my_path.empty())
    std::cout << "path empty" << std::endl;

  map_test.State_change(begin, BEGIN);
  map_test.State_change(end, END);
  map_test.show();

  return 0;
}
