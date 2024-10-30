#include "Astar.hpp"

#include <cmath>
#include <cstddef>
#include <queue>

int Astar::calc_h(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

std::stack<Node> Astar::getpath(std::pair<int, int> begin,
                                std::pair<int, int> end) {
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> OpenList;
  std::vector<std::pair<int, int>> direction = {
      {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  Node beginNode(begin.first, begin.second,
                 calc_h(begin.first, begin.second, end.first, end.second), 0,
                 nullptr);
  OpenList.push(beginNode);
  map[beginNode.x][beginNode.y] = CLOSELIST;

  while (!OpenList.empty()) {
    Node current = OpenList.top();
    OpenList.pop();

    if (current.x == end.first && current.y == end.second) {
      std::stack<Node> CloseList;
      Node *node = &current;

      while (node != nullptr) {
        CloseList.push(*node);
        map[node->x][node->y] = CLOSELIST;
        node = node->parent;
      }
      return CloseList;
    }

    for (size_t i = 0; i < direction.size(); ++i) {
      int dx = current.x + direction[i].first;
      int dy = current.y + direction[i].second;

      if (dx < 0 || dx >= row || dy < 0 || dy >= col)
        continue;
      if (map[dx][dy] != EMPTY)
        continue;
      OpenList.push(Node(dx, dy, calc_h(dx, dy, end.first, end.second),
                         current.value_g + 1, &current));
    }
  }

  return {};
}