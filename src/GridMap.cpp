#include "GridMap.hpp"

#include <iostream>

#include "colorfulUI.hpp"

State GridMap::state(std::pair<int, int>& position) {
    return Map[position.first][position.second];
}

void GridMap::updateState(const std::pair<int, int>& position, const State& state) {
    if (position.first >= 0 && position.first < row && position.second >= 0 &&
        position.second < col) {
        Map[position.first][position.second] = state;
    } else
        std::cout << "update State over range" << std::endl;
}

void GridMap::updatePath(const std::vector<std::pair<int, int>>& path) {
    for (const auto& point : path) Map[point.first][point.second] = State::PATH;
}

void GridMap::show() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            switch (Map[i][j]) {
            case State::UNKNOW:
                break;
            case State::EMPTY:
                std::cout << WHITE << "  " << RESET;
                break;
            case State::OBSTACLE:
                std::cout << BLACK << "  " << RESET;
                break;
            case State::PATH:
                std::cout << GREEN << "  " << RESET;
                break;
            case State::POINT:
                std::cout << RED << "  " << RESET;
                break;
            case State::CLOSED:
                break;
            }
        }
        std::cout << std::endl;
    }
}