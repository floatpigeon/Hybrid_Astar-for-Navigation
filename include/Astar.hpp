#pragma once

#include <math.h>

#include <cmath>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "Node.hpp"
#include "map.hpp"

class Astar {
   public:
    Astar(std::vector<std::vector<State>>& map) : Astar_map(map) {
        row = map.size();
        col = map[0].size();
    }

    float calc_h(std::pair<int, int> current, std::pair<int, int> end) {
        return (abs(current.first - end.first) + abs(current.second - end.second));
    }

    // float calc_h(std::pair<int, int> current, std::pair<int, int> end) {
    //   return sqrt(pow((current.first - end.first), 2) +
    //               pow((current.second - end.second), 2));
    // }

    float calc_g(int x1, int y1, int x2, int y2) { return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)); }
    void changeState(Node node, State state) { Astar_map[node.x][node.y] = state; }
    std::vector<std::pair<int, int>> getpath(std::pair<int, int> begin, std::pair<int, int> end);

   private:
    int row, col;
    std::vector<std::vector<State>> Astar_map;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> OpenList;
};