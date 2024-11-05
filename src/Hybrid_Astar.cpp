#include "Hybrid_Astar.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "GridMap.hpp"
#include "Node.hpp"

std::pair<int, int> Hybrid_Astar::PositionInWorldToGrid(std::pair<float, float> position) {
    int x = position.first / size;
    int y = position.second / size;
    return std::pair<int, int>(x, y);
}

std::vector<std::pair<float, float>> Hybrid_Astar::Search(std::pair<float, float> begin,
                                                          std::pair<float, float> end) {
    std::shared_ptr<Node> beginNode = std::make_shared<Node>(begin.first, begin.second, nullptr);
    std::pair<int, int> endGrid = PositionInWorldToGrid(end);

    OpenList.push(beginNode);
    while (!OpenList.empty()) {
        std::shared_ptr<Node> currentNode = OpenList.top();
        OpenList.pop();
        std::pair<int, int> currentGrid = PositionInWorldToGrid(currentNode->site());

        if (currentGrid == endGrid) {
            std::vector<std::pair<float, float>> path;
            std::shared_ptr<Node> node = currentNode;

            while (node != nullptr) {
                path.emplace_back(node->site());
                node = node->parent;
            }
            return path;
        }
        Gridmap.updateState(currentNode->site(), State::CLOSED);

        std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.5, end);

        for (const std::shared_ptr<Node>& child : children) {
            std::pair<int, int> childGrid = PositionInWorldToGrid(child->site());

            if (Gridmap.state(childGrid) == State::EMPTY) {
                OpenList.push(child);
                Gridmap.updateState(childGrid, State::OPEND);
            }
            // Grid.state内含边界判断
        }
    }
    return {};
}