#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <utility>
#include <vector>

class UI {
public:
    void Init(std::vector<std::vector<int>>& map, int n);
    void update_path(const std::vector<std::pair<float, float>>& path);
    void show();

    static void onMouse(int event, int x, int y, int flags, void* userdata);

    std::pair<float, float> get_begin() { return UI_begin; }
    std::pair<float, float> get_end() { return UI_end; }

private:
    int x, y, enlarge_num;
    cv::Mat image;
    std::pair<float, float> UI_begin;
    std::pair<float, float> UI_end;
};

/*
    前面的工作中
    HybridAstar 的坐标轴 x,y 与 OpenCV 的坐标轴反转
*/