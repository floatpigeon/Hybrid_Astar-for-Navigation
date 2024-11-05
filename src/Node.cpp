#include "Node.hpp"

// #include <Eigen/src/Core/Matrix.h>

// #include <chrono>
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
    // auto start = std::chrono::high_resolution_clock::now();

    float i = x - end.first;
    float j = y - end.second;
    if (type)
        value_h = sqrtf(i * i + j * j);
    else
        value_h = abs(i) + abs(j);

    // auto _end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = _end - start;
    // std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

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

    float branch = 16;
    for (int angle = 0; angle < branch; angle++) {
        std::pair<float, float> current(x + step * cosf(angle / branch / 2.0 * M_PI),
                                        y + step * sinf(angle / branch / 2.0 * M_PI));
        std::shared_ptr<Node> child =
            std::make_shared<Node>(current.first, current.second, shared_from_this());
        child->calc_h(end);
        children.emplace_back(child);
    }
    return children;
}

Eigen::Vector2f Node::position() const {
    return Eigen::Vector2f(x, y);
}

float Node::test(Eigen::Vector2f end, int type) {
    // auto start = std::chrono::high_resolution_clock::now();

    Eigen::Vector2f point = shared_from_this()->position() - end;
    std::cout << point.x() << "|" << point.y() << std::endl;
    if (type)
        value_h = sqrtf(point.x() * point.x() + point.y() * point.y());
    else
        value_h = std::abs(point.x()) + std::abs(point.y());

    // auto _end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = _end - start;
    // std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return value_h;
}