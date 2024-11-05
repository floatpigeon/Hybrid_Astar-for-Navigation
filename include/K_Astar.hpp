#pragma once
#include <queue>

#include "GridMap.hpp"
#include "Node.hpp"

class K_Astar {
public:
    K_Astar(GridMap map) : map(map) {}

    std::vector<std::pair<float, float>> Search(std::pair<float, float> begin,
                                                std::pair<float, float> end);

private:
    GridMap map;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> OpenList;
};