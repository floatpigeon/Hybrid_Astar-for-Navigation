/*
README
关于万能引用放在.cpp文件里
在本机环境下出现编译错误
先全部扔到.hpp文件中
*/

#include "Hybrid_Astar.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "GridMap.hpp"
#include "Node.hpp"

// inline std::pair<int, int> HybridAstar::position_in_world_to_grid(
//     std::pair<float, float> position) {
//     int x = position.first / size_;
//     int y = position.second / size_;
//     return std::pair<int, int>(x, y);
// }

// template <typename T>
// std::vector<std::pair<float, float>> HybridAstar::Search(T&& begin, T&& end) {
//     std::shared_ptr<Node> beginNode = std::make_shared<Node>(begin.first, begin.second, nullptr);
//     std::pair<int, int> endGrid = position_in_world_to_grid(end);

//     OpenList.push(beginNode);
//     while (!OpenList.empty()) {
//         std::shared_ptr<Node> currentNode = OpenList.top();
//         OpenList.pop();
//         std::pair<int, int> currentGrid = position_in_world_to_grid(currentNode->site());

//         if (currentGrid == endGrid) {
//             std::cout << "." << std::endl;

//             std::vector<std::pair<float, float>> path;
//             std::shared_ptr<Node> node = currentNode;

//             while (node != nullptr) {
//                 path.emplace_back(node->site());
//                 node = node->parent;
//             }
//             std::cout << "path find.Step:" << path.size() << std::endl;
//             for (const auto& coo : path) std::cout << coo.first << "|" << coo.second <<
//             std::endl;

//             return path;
//         }

//         gridmap_.updateState(currentNode->site(), State::CLOSED);

//         std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.5, end);

//         for (const std::shared_ptr<Node>& child : children) {
//             std::cout << ".." << std::endl;

//             std::pair<int, int> childGrid = position_in_world_to_grid(child->site());

//             if (gridmap_.state(childGrid) != State::OBSTACLE &&
//                 gridmap_.state(childGrid) != State::CLOSED) {
//                 OpenList.push(child);
//                 gridmap_.updateState(childGrid, State::OPEND);
//                 std::cout << child->site().first << " | " << child->site().second << std::endl;
//             }

//             // Grid.state内含边界判断
//         }
//     }
//     std::cout << "OpenList empty" << std::endl;

//     return {};
// }