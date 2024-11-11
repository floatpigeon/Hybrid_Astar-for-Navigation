#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "GridMap.hpp"

class MapIdentifier {
public:
    bool get_standard_grid(const std::string name);
    std::vector<std::vector<int>> identify_map(const std::string name);
    void nummap_to_gridmap(std::vector<std::vector<int>>& nummap,
                           std::vector<std::vector<State>>& gridmap);

private:
    double grid_H, grid_W;
};

/*
OPenCV 坐标系：
    横为x竖为y
    与二维数组坐标刚好转置
*/