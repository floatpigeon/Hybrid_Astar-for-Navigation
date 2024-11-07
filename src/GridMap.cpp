#include "GridMap.hpp"

#include <iostream>
#include <utility>

#include "ColorfulUI.hpp"

State GridMap::state(std::pair<int, int>& position) {
    return Map_[position.first][position.second];
}

void GridMap::update_State(const std::pair<int, int>& position, const State& state) {
    Map_[position.first][position.second] = state;
}

void GridMap::update_Path(const std::vector<std::pair<int, int>>& path) {
    for (const std::pair<int, int>& point : path) Map_[point.first][point.second] = State::PATH;
}

void GridMap::show() {
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < col_; j++) {
            switch (Map_[i][j]) {
            case State::EMPTY:
            case State::CLOSED:
            case State::OPEND:

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
            case State::UNKNOW:
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool GridMap::is_in_bounds(std::pair<int, int>& position) {
    if (position.first < 0 || position.first >= row_ || position.second < 0 ||
        position.second >= col_)
        return false;
    else
        return true;
}