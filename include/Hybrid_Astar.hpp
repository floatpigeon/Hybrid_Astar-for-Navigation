#pragma once
#include <queue>

#include "GridMap.hpp"
#include "Node.hpp"
class Hybrid_Astar {
public:
    Hybrid_Astar(GridMap& map, float size = 1) : Gridmap(map), size(size) {}

    std::pair<int, int> PositionInWorldToGrid(std::pair<float, float> position);

    std::vector<std::pair<float, float>> Search(std::pair<float, float> begin,
                                                std::pair<float, float> end);

private:
    float size;
    GridMap& Gridmap;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, GreaterNode>
        OpenList;
};