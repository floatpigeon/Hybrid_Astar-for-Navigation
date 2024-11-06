#pragma once
#include <utility>
#include <vector>

enum class State : unsigned char { UNKNOW, EMPTY, OBSTACLE, PATH, CLOSED, OPEND, POINT };

class GridMap {
public:
    GridMap(std::vector<std::vector<State>>&& map) : Map_(map) {
        row_ = map.size();
        col_ = map[0].size();
    }

    bool is_in_bounds(std::pair<int, int>& position);
    State state(std::pair<int, int>& position);
    void update_State(const std::pair<int, int>& position, const State& state);
    void update_Path(const std::vector<std::pair<int, int>>& path);
    void show();

private:
    int row_, col_;
    std::vector<std::vector<State>>& Map_;
};
