#pragma once
#include <utility>
#include <vector>

enum class State : unsigned char { UNKNOW, EMPTY, OBSTACLE, PATH, CLOSED, OPEND, POINT };

class GridMap {
public:
    GridMap(std::vector<std::vector<State>>&& map) : Map(map) {
        row = map.size();
        col = map[0].size();
    }
    State state(std::pair<int, int>& position);
    void updateState(const std::pair<int, int>& position, const State& state);
    void updatePath(const std::vector<std::pair<int, int>>& path);
    void show();

private:
    int row, col;
    std::vector<std::vector<State>>& Map;
};
