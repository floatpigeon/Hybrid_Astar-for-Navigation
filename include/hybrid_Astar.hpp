#pragma once

#include <Node.hpp>
#include <cmath>
#include <functional>
#include <map.hpp>
#include <math.h>
#include <queue>
#include <utility>
#include <vector>

class HybridAstar {
public:
  HybridAstar(std::vector<std::vector<State>> &map) : gridmap(map) {
    row = map.size();
    col = map[0].size();
  }

  float calc_h(std::pair<int, int> current, std::pair<int, int> end) {
    return (abs(current.first - end.second) + abs(current.first - end.second));
  }
  float calc_g(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
  }

  void changeState(Node node, State state) { gridmap[node.x][node.y] = state; }
  std::vector<Node> getpath(std::pair<int, int> begin, std::pair<int, int> end);

private:
  int row, col;
  std::vector<std::vector<State>> gridmap;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> OpenList;
};