#include "map_identifier.hpp"

#include <opencv2/calib3d.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

#include "GridMap.hpp"

void MapIdentifier::nummap_to_gridmap(std::vector<std::vector<int>>& nummap,
                                      std::vector<std::vector<State>>& gridmap) {
    for (std::size_t i = 0; i < nummap.size(); i++) {
        for (std::size_t j = 0; j < nummap[0].size(); j++) {
            if (nummap[i][j] == 1) {
                gridmap[i][j] = State::OBSTACLE;
            } else
                gridmap[i][j] = State::EMPTY;
        }
    }
}

bool MapIdentifier::get_standard_grid(const std::string name) {
    cv::Mat standard_image = cv::imread(name);
    if (standard_image.empty()) {
        std::cout << "can't find standard iamge" << std::endl;
        return false;
    }
    cv::Mat gray;
    cv::cvtColor(standard_image, gray, cv::COLOR_BGR2GRAY);

    cv::Size patternSize(11, 11);
    std::vector<cv::Point2f> corners;
    bool found = cv::findChessboardCorners(gray, patternSize, corners);

    if (!found) {
        std::cout << "No corners" << std::endl;
        return false;
    }

    cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                     cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));

    int num_h = 0;
    int num_w = 0;
    double sum_h = 0;
    double sum_w = 0;

    for (int i = 0; i < patternSize.height - 1; ++i) {
        for (int j = 0; j < patternSize.width - 1; ++j) {
            int idx = i * patternSize.width + j;
            double height = cv::norm(corners[idx + patternSize.width] - corners[idx]);
            double width = cv::norm(corners[idx + 1] - corners[idx]);

            sum_h += height;
            sum_w += width;

            num_h++;
            num_w++;
        }
    }
    grid_H = sum_h / num_h;
    grid_W = sum_w / num_w;

    std::cout << "height " << grid_H << "points" << std::endl;
    std::cout << "width " << grid_W << "points" << std::endl;
    return true;
}

std::vector<std::vector<int>> MapIdentifier::identify_map(const std::string name) {
    cv::Mat map_image = cv::imread(name);
    if (map_image.empty()) {
        std::cout << "can't find standard iamge" << std::endl;
        return {};
    }

    cv::Mat gray;
    cv::cvtColor(map_image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat binary;
    cv::threshold(gray, binary, 125, 255, cv::THRESH_BINARY);

    int map_row = binary.rows / grid_H;
    int map_col = binary.cols / grid_W;
    std::vector<std::vector<int>> num_map(map_row, std::vector<int>(map_col, 0));

    for (int i = 0; i < map_row; i++) {
        for (int j = 0; j < map_col; j++) {
            cv::Point p(j * grid_W, i * grid_H);
            uchar value = binary.at<uchar>(p);
            if (static_cast<int>(value) == 255) {
                // std::cout << static_cast<int>(value) << std::endl;
                num_map[i][j] = 0;
            } else {
                // std::cout << static_cast<int>(value) << std::endl;
                num_map[i][j] = 1;
            }
        }
    }

    // for (int i = 0; i < num_map.size(); i++) {
    //     for (int j = 0; j < num_map[0].size(); j++) {
    //         std::cout << num_map[i][j];
    //     }
    //     std::cout << std::endl;
    // }

    return num_map;
}