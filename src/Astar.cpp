#include "Astar.hpp"
#include "Node.hpp"
#include "map.hpp"
#include <cstddef>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> Astar::getpath(std::pair<int, int> begin,
                                                std::pair<int, int> end) {
  std::vector<std::pair<int, int>> direction = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  Node *beginNode =
      new Node(begin.first, begin.second, 0, calc_h(begin, end), nullptr);

  OpenList.push(*beginNode);
  changeState(*beginNode, CLOSED);

  while (!OpenList.empty()) {
    Node currentNode = OpenList.top();
    OpenList.pop();
    changeState(currentNode, CLOSED);

    if (currentNode.x == end.first && currentNode.y == end.second) {
      std::vector<std::pair<int, int>> path;
      Node *node = new Node(currentNode);
      std::cout << "result" << std::endl;

      while (node != nullptr) {
        path.emplace_back(node->position());
        changeState(*node, PATH);
        auto ptr = node;
        node = node->parent;
        delete ptr;
      }
      delete node;
      return path;
    }

    for (size_t i = 0; i < direction.size(); i++) {

      std::pair<int, int> next;
      next.first = currentNode.x + direction[i].first;
      next.second = currentNode.y + direction[i].second;

      if (next.first < 0 || next.first >= row || next.second < 0 ||
          next.second >= col)
        continue;
      if (Astar_map[next.first][next.second] != EMPTY)
        continue;

      Node *parent = new Node(currentNode);
      Node *openNode =
          new Node(next.first, next.second,
                   calc_g(next.first, next.second, parent->x, parent->y),
                   calc_h(next, end), parent);

      OpenList.push(*openNode);
      changeState(*openNode, OPEND);

      delete openNode;
    }
  }
  return {};
}