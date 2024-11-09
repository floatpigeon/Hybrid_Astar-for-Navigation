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
    int times = 0;
    std::shared_ptr<Node> beginNode = std::make_shared<Node>(begin.first, begin.second, nullptr);
    beginNode->calc_h(end);
    std::pair<int, int> endGrid = position_in_world_to_grid(end);

    OpenList_.push(beginNode);
    while (!OpenList_.empty()) {
        times++;
        std::shared_ptr<Node> currentNode = OpenList_.top();
        OpenList_.pop();
        std::pair<int, int> currentGrid = position_in_world_to_grid(currentNode->site());

        if (currentGrid == endGrid) {
            std::cout << "find it" << std::endl;

            std::vector<std::pair<float, float>> path;
            std::shared_ptr<Node> node = currentNode;

            while (node != nullptr) {
                // 可视化测试
                std::pair<int, int> pathgrid = position_in_world_to_grid(node->site());
                gridmap_.update_State(pathgrid, State::PATH);
                //
                path.emplace_back(node->site());
                node = node->parent;
            }
            std::cout << "path find.Step:" << path.size() << std::endl;
            for (const auto& coo : path) std::cout << coo.first << "|" << coo.second << std::endl;
            gridmap_.show();
            std::cout << times << std::endl;
            return path;
        }

        gridmap_.update_State(currentNode->site(), State::CLOSED);

        std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.8, end);

        for (const std::shared_ptr<Node>& child : children) {
            if (accessible(child)) {
                std::cout << "push it" << std::endl;
                OpenList_.push(child);
            }
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

inline bool HybridAstar::accessible(const std::shared_ptr<Node>& node) {
    std::cout << "judge begin:  " << node->site().first << " | " << node->site().second
              << std::endl;
    std::pair<int, int> nodeGrid = position_in_world_to_grid(node->site());
    // 子节点越界判断
    if (!gridmap_.is_in_bounds(nodeGrid)) {
        std::cout << "over range" << std::endl;
        return false;
    }
    // 子节点状态判断
    if (gridmap_.state(nodeGrid) == State::OBSTACLE || gridmap_.state(nodeGrid) == State::CLOSED) {
        std::cout << "state wrong" << std::endl;
        return false;
    }
    // 重复选择判断
    std::pair<int, int> parentGrid = position_in_world_to_grid(node->parent->site());
    if (nodeGrid == parentGrid) {
        std::cout << "reselect" << std::endl;
        return false;
    }
    // 子节点路径判断
    if (abs(nodeGrid.first - parentGrid.first) > 1 ||
        abs(nodeGrid.second - parentGrid.second) > 1) {
        std::pair<int, int> midGrid((nodeGrid.first + parentGrid.first) / 2,
                                    (nodeGrid.second + parentGrid.first) / 2);
        if (gridmap_.state(midGrid) == State::OBSTACLE || gridmap_.state(midGrid) == State::CLOSED)
            return false;
    }

    return true;
}