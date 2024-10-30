#ifndef PROJECT_H
#define PROJECT_H

#include <Node.hpp>
#include <stack>
#include <vector>

enum State { EMPTY, OBSTACLE, CLOSELIST };

class Astar {
public:
  Astar(std::vector<std::vector<State>> &map) : map(map) {
    row = map.size();
    col = map[0].size();
  }

  int calc_h(int x1, int y1, int x2, int y2);

  std::stack<Node> getpath(std::pair<int, int> begin, std::pair<int, int> end);

private:
  std::vector<std::vector<State>> map;
  int row, col;
};

#endif