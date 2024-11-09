#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <utility>
#include <vector>

class UI {
public:
    void Init(std::vector<std::vector<int>>& map, int n);
    void update_path(const std::vector<std::pair<float, float>>& path);
    std::pair<float, float> get_edge_point();
    void show();

private:
    int x, y, n;
    cv::Mat image;
};

/*
    前面的工作中
    HybridAstar 的坐标轴 x,y 与 OpenCV 的坐标轴反转
*/