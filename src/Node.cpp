#include "Node.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

float Node::calc_g() {
    if (parent != nullptr) {
        float i = x_ - parent->x_;
        float j = y_ - parent->y_;
        value_g_ = sqrtf(i * i + j * j) + parent->value_g_;
    } else
        value_g_ = 0;

    return value_g_;
}

float Node::calc_h(std::pair<float, float> end, int type) {
    float i = x_ - end.first;
    float j = y_ - end.second;
    float turn_punishment =
        0.2 * (parent == nullptr ? 0 : (log(1 + abs((parent->angle - angle) / 2))));

    value_h_ = sqrtf(i * i + j * j) + turn_punishment;

    return value_h_;
}

std::vector<std::shared_ptr<Node>> Node::GenerateChildren(float step,
                                                          std::pair<float, float>& end) {
    std::vector<std::shared_ptr<Node>> children;

    if (shared_from_this()->calc_h(end, 1) <= step) {
        std::shared_ptr<Node> endNode =
            std::make_shared<Node>(end.first, end.second, end, shared_from_this());
        children.emplace_back(endNode);
        std::cout << "finish" << std::endl;
        return children;
    }

    int branch = 36;

    for (int i = 0; i < branch; i++) {
        double angle = static_cast<double>(i) / branch * 2.0 * M_PI;
        std::pair<float, float> current(x_ + step * cos(angle), y_ + step * sin(angle));

        std::shared_ptr<Node> child =
            std::make_shared<Node>(current.first, current.second, end, shared_from_this());

        child->angle = angle;
        child->calc_h(end);
        children.push_back(child);
    }
    return children;
}
