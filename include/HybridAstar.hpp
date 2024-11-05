#pragma once
#include <iostream>
#include <queue>

#include "GridMap.hpp"
#include "Node.hpp"
class HybridAstar {
public:
    HybridAstar(GridMap& map, float size = 1) : gridmap_(map), size_(size) {}

    inline std::pair<int, int> position_in_world_to_grid(std::pair<float, float> position);

    // 万能引用
    template <typename T>
    std::vector<std::pair<float, float>> Search(T&& begin, T&& end);

private:
    float size_;
    GridMap& gridmap_;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, GreaterNode>
        OpenList_;
};

template <typename T>
std::vector<std::pair<float, float>> HybridAstar::Search(T&& begin, T&& end) {
    std::shared_ptr<Node> beginNode = std::make_shared<Node>(begin.first, begin.second, nullptr);
    std::pair<int, int> endGrid = position_in_world_to_grid(end);

    OpenList_.push(beginNode);
    while (!OpenList_.empty()) {
        std::shared_ptr<Node> currentNode = OpenList_.top();
        OpenList_.pop();
        std::pair<int, int> currentGrid = position_in_world_to_grid(currentNode->site());

        if (currentGrid == endGrid) {
            std::cout << "." << std::endl;

            std::vector<std::pair<float, float>> path;
            std::shared_ptr<Node> node = currentNode;

            while (node != nullptr) {
                path.emplace_back(node->site());
                node = node->parent;
            }
            std::cout << "path find.Step:" << path.size() << std::endl;
            for (const auto& coo : path) std::cout << coo.first << "|" << coo.second << std::endl;

            return path;
        }

        gridmap_.updateState(currentNode->site(), State::CLOSED);

        std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.5, end);

        for (const std::shared_ptr<Node>& child : children) {
            std::cout << ".." << std::endl;

            std::pair<int, int> childGrid = position_in_world_to_grid(child->site());

            if (gridmap_.state(childGrid) != State::OBSTACLE &&
                gridmap_.state(childGrid) != State::CLOSED) {
                OpenList_.push(child);
                gridmap_.updateState(childGrid, State::OPEND);
                std::cout << child->site().first << " | " << child->site().second << std::endl;
            }

            // Grid.state内含边界判断
        }
    }
    std::cout << "OpenList empty" << std::endl;

    return {};
}

inline std::pair<int, int> HybridAstar::position_in_world_to_grid(
    std::pair<float, float> position) {
    int x = position.first / size_;
    int y = position.second / size_;
    return std::pair<int, int>(x, y);
}
