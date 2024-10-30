#include "Node.hpp"
#include "map.hpp"
#include <cstddef>
#include <hybrid_Astar.hpp>
#include <queue>
#include <utility>
#include <vector>

std::vector<Node> HybridAstar::getpath(std::pair<int, int> begin,
                                       std::pair<int, int> end) {
  std::vector<std::pair<int, int>> direction;
  Node beginNode(begin.first, begin.second, 0, calc_h(begin, end), nullptr);

  OpenList.push(beginNode);
  changeState(beginNode, CLOSED);

  while (!OpenList.empty()) {
    Node currentNode = OpenList.top();
    OpenList.pop();

    if (currentNode.x == end.first && currentNode.y == end.second) {
      std::vector<Node> path;
      Node *node = &currentNode;

      while (node != nullptr) {
        path.emplace_back(node);
        changeState(*node, CLOSED);
        node = node->parent;
      }

      return path;
    }

    for (size_t i; i < direction.size(); i++) {
      std::pair<int, int> next;
      next.first = currentNode.x + direction[i].first;
      next.second = currentNode.y + direction[i].second;

      if (next.first < 0 || next.first >= row || next.second < 0 ||
          next.second >= col)
        continue;
      if (gridmap[next.first][next.second] != EMPTY)
        continue;

      Node openNode(
          next.first, next.second,
          calc_g(next.first, next.second, currentNode.x, currentNode.y),
          calc_h(next, end), &currentNode);

      OpenList.push(openNode);
      changeState(openNode, OPEND);
    }
  }
  return {};
}