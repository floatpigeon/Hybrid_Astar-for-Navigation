#include <iostream>
#include <opencv2/highgui.hpp>
#include <utility>
#include <vector>

#include "EZUI.hpp"
#include "GridMap.hpp"
#include "HybridAstar.hpp"
#include "map_identifier.hpp"

int main() {
    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    MapIdentifier MapI_;
    if (!MapI_.get_standard_grid("../include/maps/standard_image.png")) {
        return -1;
    }
    std::vector<std::vector<int>> num_map = MapI_.identify_map("../include/maps/map.png");

    std::vector<std::vector<State>> state_map(num_map.size(),
                                              std::vector<State>(num_map[0].size(), State::UNKNOW));

    float rate = 20.0;
    GridMap my_map(std::move(state_map));
    UI ui;
    ui.Init(num_map, rate);
    ui.show();

    cv::setMouseCallback("Navigation", UI::onMouse, &ui);
    while (true) {
        std::pair<float, float> begin = {ui.get_begin().first / rate, ui.get_begin().second / rate};
        std::pair<float, float> end = {ui.get_end().first / rate, ui.get_end().second / rate};

        if (cv::waitKey(10) == 'l') {
            std::cout << begin.first << "," << begin.second << std::endl;
            std::cout << end.first << "," << end.second << std::endl;
        }

        if (cv::waitKey(10) == 13) {
            std::cout << ".." << std::endl;
            MapI_.nummap_to_gridmap(num_map, state_map);
            HybridAstar my_Astar(my_map);
            std::vector<std::pair<float, float>> path = my_Astar.Search(begin, end);
            ui.Init(num_map, rate);
            ui.update_path(path);
            ui.show();
        }
    }
    return 0;
}
