#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>

#include "GridMap.hpp"
#include "Node.hpp"
class HybridAstar {
public:
    HybridAstar(GridMap& map, float size = 1) : gridmap_(map), size_(size) {}

    inline std::pair<int, int> position_in_world_to_grid(std::pair<float, float> position);
    inline bool accessible(const std::shared_ptr<Node>& node);

    template <typename T>
    std::vector<std::pair<float, float>> Search(T&& begin, T&& end);

private:
    float size_;
    GridMap& gridmap_;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, GreaterNode>
        OpenList_;
};

/*-------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

template <typename T>
std::vector<std::pair<float, float>> HybridAstar::Search(T&& begin, T&& end) {
    std::shared_ptr<Node> beginNode =
        std::make_shared<Node>(begin.first, begin.second, end, nullptr);
    std::pair<int, int> endGrid = position_in_world_to_grid(end);

    OpenList_.push(beginNode);
    while (!OpenList_.empty()) {
        std::shared_ptr<Node> currentNode = OpenList_.top();
        OpenList_.pop();
        std::pair<int, int> currentGrid = position_in_world_to_grid(currentNode->site());

        if (gridmap_.state(currentGrid) == State::CLOSED) {
            continue;
        }

        if (currentGrid == endGrid) {
            std::cout << "find it" << std::endl;

            std::vector<std::pair<float, float>> path;
            std::shared_ptr<Node> node = std::make_shared<Node>(
                currentNode->site().first, currentNode->site().second, end, currentNode);

            while (node != nullptr) {
                // 可视化测试
                std::pair<int, int> pathgrid = position_in_world_to_grid(node->site());
                gridmap_.update_State(pathgrid, State::PATH);
                //
                path.emplace_back(node->site());
                node = node->parent;
            }
            std::cout << "path find.Step:" << path.size() << std::endl;
            for (const auto& coo : path) std::cout << coo.first << " | " << coo.second << std::endl;
            gridmap_.show();

            return path;
        }

        gridmap_.update_State(currentNode->site(), State::CLOSED);

        std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.6, end);

        for (const std::shared_ptr<Node>& child : children) {
            if (accessible(child)) {
                OpenList_.push(child);
            }
        }
    }
    std::cout << "path empty" << std::endl;

    return {};
}

inline std::pair<int, int> HybridAstar::position_in_world_to_grid(
    std::pair<float, float> position) {
    int x = static_cast<double>(position.first / size_);
    int y = static_cast<double>(position.second / size_);
    // int x = position.first / static_cast<float>(size_) - 0.5;
    // int y = position.second / static_cast<float>(size_) - 0.5;
    return std::pair<int, int>(x, y);
}

inline bool HybridAstar::accessible(const std::shared_ptr<Node>& node) {
    std::pair<int, int> nodeGrid = position_in_world_to_grid(node->site());
    // 子节点越界判断
    if (!gridmap_.is_in_bounds(nodeGrid)) {
        return false;
    }
    // 子节点状态判断
    if (gridmap_.state(nodeGrid) == State::OBSTACLE || gridmap_.state(nodeGrid) == State::CLOSED) {
        return false;
    }
    // 重复选择判断
    std::pair<int, int> parentGrid = position_in_world_to_grid(node->parent->site());
    if (nodeGrid == parentGrid) {
        return false;
    }
    // 子节点路径判断

    return true;
}
