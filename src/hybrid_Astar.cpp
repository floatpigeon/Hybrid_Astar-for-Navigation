#include "hybrid_Astar.hpp"
#include "Node.hpp"
#include "map.hpp"
#include <cstddef>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> HybridAstar::getpath(std::pair<int, int> begin,
                                                      std::pair<int, int> end) {
  std::vector<std::vector<State>> grid(
      row / Grid_size, std::vector<State>(col / Grid_size, UNKNOW));

  for (int i = 0; i < row; i++) {
    int x = i / Grid_size;
    for (int j = 0; j < col; j++) {
      int y = j / Grid_size;
      if (grid[x][y] == UNKNOW) {
        if (Astar_map[i][j] == OBSTACLE)
          grid[x][y] = OBSTACLE;
        else
          grid[x][y] = EMPTY;
      }
    }
  }

  std::vector<std::pair<int, int>> direction = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  Node *beginNode =
      new Node(begin.first, begin.second, 0, calc_h(begin, end), nullptr);
  OpenList.push(*beginNode);
  grid[beginNode->x / Grid_size][beginNode->y / Grid_size] = CLOSED;

  while (!OpenList.empty()) {
    Node currentNode = OpenList.top();
    OpenList.pop();
    grid[beginNode->x / Grid_size][beginNode->y / Grid_size] = CLOSED;

    if (currentNode.x / Grid_size == end.first / Grid_size &&
        currentNode.y / Grid_size == end.second / Grid_size) {

      std::vector<std::pair<int, int>> path;
      Node *node = new Node(currentNode);
      std::cout << "result" << std::endl;

      while (node->parent != nullptr) {
        auto ptr = node;
        node = node->parent;
        path.emplace_back(node->position());
        changeState(*node, PATH);
        delete ptr;
      }
      delete node;
      return path;
    }

    for (size_t i = 0; i < direction.size(); i++) {
      std::pair<int, int> nextgrid;
      nextgrid.first = currentNode.x / Grid_size + direction[i].first;
      nextgrid.second = currentNode.y / Grid_size + direction[i].second;

      std::pair<int, int> next;
      next.first = nextgrid.first * Grid_size;
      next.second = nextgrid.second * Grid_size;

      if (nextgrid.first < 0 || nextgrid.first >= row / Grid_size ||
          nextgrid.second < 0 || nextgrid.second >= col / Grid_size)
        continue;
      if (grid[nextgrid.first][nextgrid.second] != EMPTY)
        continue;

      Node *parent = new Node(currentNode);
      Node *openNode =
          new Node(next.first, next.second,
                   calc_g(next.first, next.second, parent->x, parent->y),
                   calc_h(next, end), parent);

      OpenList.push(*openNode);
      grid[nextgrid.first][nextgrid.second] = OPEND;

      delete openNode;
    }
  }
  return {};
}