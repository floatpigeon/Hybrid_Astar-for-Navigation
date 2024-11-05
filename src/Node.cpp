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
    if (type)
        value_h = sqrtf(i * i + j * j);
    else
        value_h = std::abs(i) + std::abs(j);
    return value_h;
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

    for (int angle = 0; angle < 8; angle++) {
        std::pair<float, float> current(x + step * cosf(angle / 4.0 * M_PI),
                                        y + step * sinf(angle / 4.0 * M_PI));
        std::shared_ptr<Node> child =
            std::make_shared<Node>(current.first, current.second, shared_from_this());
        child->calc_h(end);
        children.emplace_back(child);
    }
    return children;
}
