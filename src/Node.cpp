#include "Node.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

std::pair<float, float> Node::site() const {
    return {x, y};
}

float Node::calc_g() {
    if (parent != nullptr) {
        float i = x - parent->x;
        float j = y - parent->y;
        value_g = sqrtf(i * i + j * j) + parent->value_g;
    } else
        value_g = 0;

    return value_g;
}

float Node::calc_h(std::pair<float, float> end, int type) {
    float i = x - end.first;
    float j = y - end.second;
    float h;
    if (type)
        h = sqrtf(i * i + j * j);
    else
        h = abs(i) + abs(j);

    value_h = h;

    return h;
}

float Node::value_f() const {
    return value_g + value_h;
};

std::vector<std::shared_ptr<Node>> Node::GenerateChildren(float step,
                                                          std::pair<float, float>& end) {
    std::vector<std::shared_ptr<Node>> children;

    if (shared_from_this()->calc_h(end, 1) <= step) {
        std::shared_ptr<Node> endNode =
            std::make_shared<Node>(end.first, end.second, shared_from_this());
        children.emplace_back(endNode);
        std::cout << "finish" << std::endl;
        return children;
    }
    std::cout << "current:" << shared_from_this()->site().first << "|"
              << shared_from_this()->site().second << std::endl;

    int branch = 8;
    std::cout << "children:" << std::endl;

    for (int i = 0; i < branch; i++) {
        double angle = static_cast<double>(i) / branch * 2.0 * M_PI;
        std::pair<float, float> current(x + step * cos(angle), y + step * sin(angle));

        std::cout << current.first << " | " << current.second << std::endl;

        std::shared_ptr<Node> child =
            std::make_shared<Node>(current.first, current.second, shared_from_this());

        child->calc_h(end);
        children.emplace_back(child);
    }
    return children;
}
