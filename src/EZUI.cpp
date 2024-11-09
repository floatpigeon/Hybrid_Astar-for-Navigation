#include "EZUI.hpp"

#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <ostream>
#include <utility>

void UI::Init(std::vector<std::vector<int>>& map, int enlarge_num) {
    //
    n = enlarge_num;
    int rows = map.size();
    int cols = map[0].size();

    cv::Mat original(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original.at<uchar>(i, j) = 255;
        }
    }

    cv::Mat enlarged;
    cv::resize(original, enlarged, cv::Size(), n, n, cv::INTER_NEAREST);

    image = enlarged;
}

void UI::show() {
    cv::imshow("Navigation", image);
    if (cv::waitKey(0) == 'q') cv::destroyAllWindows();
}

void UI::update_path(const std::vector<std::pair<float, float>>& path) {
    for (const auto& position : path) {
        cv::Point site(position.second * n, position.first * n);
        cv::circle(image, site, 3, cv::Scalar(0, 0, 255), -1);
    }
}

// std::pair<float, float> UI::get_edge_point() {}

// void mouseCallback(int event, int x, int y, int flags, void* userdata) {
//     if (event == cv::EVENT_LBUTTONDOWN) {
//         std::cout << "Mouse clicked at (" << x << ", " << y << ")" << std::endl;

//         cv::Mat* image = static_cast<cv::Mat*>(userdata);
//         cv::circle(*image, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
//     }
// }
