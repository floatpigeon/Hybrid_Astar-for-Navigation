#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <queue>
#include <utility>
#include <vector>

#include "GridMap.hpp"
#include "HybridAstar.hpp"
#include "Node.hpp"

void nummap_to_gridmap(std::vector<std::vector<int>>& nummap,
                       std::vector<std::vector<State>>& gridmap) {
    for (std::size_t i = 0; i < nummap.size(); i++) {
        for (std::size_t j = 0; j < nummap[0].size(); j++) {
            if (nummap[i][j]) {
                gridmap[i][j] = State::OBSTACLE;
            } else
                gridmap[i][j] = State::EMPTY;
        }
    }
}

std::pair<int, int> PositionInWorldToGrid(std::pair<float, float> position) {
    int x = position.first;
    int y = position.second;
    return std::pair<int, int>(x, y);
}

int main() {
    // std::pair<float, float> end(6.0, 0);
    // std::shared_ptr<Node> node_0 = std::make_shared<Node>(0, 0);
    // node_0->calc_h(end);
    // std::shared_ptr<Node> node_1 = std::make_shared<Node>(1, 0, node_0);
    // node_1->calc_h(end);
    // std::shared_ptr<Node> node_2 = std::make_shared<Node>(5, 0, node_1);
    // std::cout << node_0->value_f() << std::endl;

    // std::vector<std::vector<int>> num_map = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}};
    // std::vector<std::vector<State>> map(num_map.size(),
    //                                     std::vector<State>(num_map[0].size(), State::EMPTY));
    // std::cout << ".." << std::endl;

    // for (int i = 0; i < num_map.size(); i++) {
    //     for (int j = 0; j < num_map[0].size(); j++) {
    //         if (num_map[i][j]) map[i][j] = State::OBSTACLE;
    //     }
    // }
    //---------------------------------------------------------------------------------------------

    // GridMap mymap(std::move(map));
    // std::pair<int, int> site(1, 0);
    // mymap.updateState(site, State::CLOSED);

    // if (mymap.state(site) == State::CLOSED) {
    //     std::cout << "..." << std::endl;
    // } else
    //     std::cout << "___" << std::endl;
    //---------------------------------------------------------------------------------------------

    // std::priority_queue<Node, std::vector<Node>, std::greater<Node>> OpenList;
    // std::pair<float, float> end(2, 2);

    // std::shared_ptr<Node> beginNode = std::make_shared<Node>(1, 1, nullptr);
    // OpenList.push(*beginNode);

    // std::shared_ptr<Node> currentNode = std::make_shared<Node>(OpenList.top());
    // std::vector<std::shared_ptr<Node>> children = currentNode->GenerateChildren(1.5, end);
    // for (const auto& point : children)
    //     std::cout << point->site().first << "|" << point->site().second << std::endl;

    // Eigen::Vector2f E_end(2.0, 2.0);
    // currentNode->test(E_end);
    //---------------------------------------------------------------------------------------------

    // std::vector<std::vector<int>> my_num_map = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}};
    // std::vector<std::vector<State>> my_grid_map(
    //     my_num_map.size(), std::vector<State>(my_num_map[0].size(), State::UNKNOW));
    // NummapToGridmap(my_num_map, my_grid_map);
    // GridMap my_map(std::move(my_grid_map));
    // std::pair<int, int> z(1, 0);
    // if (my_map.state(z) == State::OBSTACLE) {
    //     std::cout << ".." << std::endl;
    // }

    // std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, GreaterNode>
    //     OpenList;

    // std::pair<float, float> end(2.0, 2.0);
    // std::shared_ptr<Node> beginNode = std::make_shared<Node>(0, 1, nullptr);
    // OpenList.push(beginNode);

    // std::vector<std::shared_ptr<Node>> children = beginNode->GenerateChildren(1, end);

    // for (const auto& point : children) {
    //     auto n = PositionInWorldToGrid(point->site());

    //     std::cout << n.first << " " << n.second << std::endl;

    //     if (my_map.state(n) == State::EMPTY) {
    //         std::cout << "T" << std::endl;
    //         OpenList.push(point);
    //     } else
    //         std::cout << "F" << std::endl;
    // }

    // while (!OpenList.empty()) {
    //     std::cout << OpenList.top()->value_f() << " | " << OpenList.top()->site().first << " | "
    //               << OpenList.top()->site().second << std::endl;
    //     OpenList.pop();
    // }
    //---------------------------------------------------------------------------------------------

    std::vector<std::vector<int>> my_num_map = {
        {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 1}};
    std::vector<std::vector<State>> my_grid_map(
        my_num_map.size(), std::vector<State>(my_num_map[0].size(), State::UNKNOW));
    nummap_to_gridmap(my_num_map, my_grid_map);
    GridMap my_map(std::move(my_grid_map));

    HybridAstar my_Astar(my_map);
    my_Astar.Search(std::pair<float, float>{0, 0}, std::pair<float, float>{2, 3});

    //---------------------------------------------------------------------------------------------

    return 0;
}
