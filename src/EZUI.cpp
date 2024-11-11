#include "EZUI.hpp"

#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <utility>

void UI::Init(std::vector<std::vector<int>>& map, int n) {
    enlarge_num = n;
    int rows = map.size();
    int cols = map[0].size();

    cv::Mat original(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original.at<uchar>(i, j) = 1 == map[i][j] ? 0 : 255;
        }
    }

    cv::Mat enlarged;
    cv::resize(original, enlarged, cv::Size(), enlarge_num, enlarge_num, cv::INTER_NEAREST);

    image = enlarged;
}

void UI::show() {
    cv::imshow("Navigation", image);

    // if (cv::waitKey(0) == 'q') cv::destroyAllWindows();
}

void UI::update_path(const std::vector<std::pair<float, float>>& path) {
    for (const auto& position : path) {
        cv::Point site(position.second * enlarge_num, position.first * enlarge_num);
        cv::circle(image, site, 3, cv::Scalar(0, 0, 255), -1);
    }
}

void UI::onMouse(int event, int x, int y, int flags, void* userdata) {
    UI* ptr = reinterpret_cast<UI*>(userdata);

    if (event == cv::EVENT_LBUTTONDOWN) {
        if (flags & cv::EVENT_FLAG_CTRLKEY) {
            ptr->UI_begin = {y, x};
            std::cout << "save the begin point: " << x << "," << y << " on UI" << std::endl;
        }
        if (flags & cv::EVENT_FLAG_SHIFTKEY) {
            ptr->UI_end = {y, x};
            std::cout << "save the end point:   " << x << "," << y << " on UI" << std::endl;
        }
    }
}
