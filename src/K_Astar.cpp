#include "K_Astar.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "Node.hpp"

std::vector<std::pair<float, float>> K_Astar::Search(std::pair<float, float> begin,
                                                     std::pair<float, float> end) {
    std::shared_ptr<Node> beginNode = std::make_shared<Node>(begin.first, begin.second);
    OpenList.push(*beginNode);

    while (!OpenList.empty()) {
        std::shared_ptr<Node> currentNode = std::make_shared<Node>(OpenList.top());
        OpenList.pop();

        if (currentNode->site() == end) {
            std::vector<std::pair<float, float>> path;
            std::shared_ptr<Node> node = std::make_shared<Node>(currentNode);

            while (node != nullptr) {
                path.emplace_back(node->site());
                std::shared_ptr<Node> ptr = node;
                node = node->parent;
            }
            return path;
        }

        std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1, end);

        // judge it can arrive ?
        for (const std::shared_ptr<Node>& child : children) {
            if (true) {
                OpenList.push(*child);
            }
        }
    }
    return {};
}