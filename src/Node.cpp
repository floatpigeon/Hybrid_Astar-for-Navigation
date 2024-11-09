#include "Node.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

std::pair<float, float> Node::site() const {
    return {x_, y_};
}

float Node::calc_g() {
    if (parent != nullptr) {
        float i = x_ - parent->x_;
        float j = y_ - parent->y_;
        value_g_ = 1 + parent->value_g_;
    } else
        value_g_ = 0;

    return value_g_;
}

float Node::calc_h(std::pair<float, float>& end, int type) {
    float i = x_ - end.first;
    float j = y_ - end.second;
    float h;
    if (type)
        h = sqrtf(i * i + j * j) +
            0.2 * (parent == nullptr ? 0 : (log(1 + abs(asin(sin((parent->angle - angle) / 2))))));
    else
        h = abs(i) + abs(j);

    value_h_ = h;

    return h;
}

float Node::value_f() const {
    return value_g_ + value_h_;
};

std::vector<std::shared_ptr<Node>> Node::GenerateChildren(float step,
                                                          std::pair<float, float>& end) {
    std::vector<std::shared_ptr<Node>> children;

    // if (shared_from_this()->calc_h(end, 1) <= step * 0.5) {
    //     std::shared_ptr<Node> endNode =
    //         std::make_shared<Node>(end.first, end.second, shared_from_this());
    //     children.emplace_back(endNode);
    //     std::cout << "finish" << std::endl;
    //     return children;
    // }

    int branch = 36;
    // std::cout << "children:" << std::endl;

    for (int i = 0; i < branch; i++) {
        double angle = static_cast<double>(i) / branch * 2.0 * M_PI;
        std::pair<float, float> current(x_ + step * cos(angle), y_ + step * sin(angle));

        // std::cout << current.first << " | " << current.second << std::endl;

        std::shared_ptr<Node> child =
            std::make_shared<Node>(current.first, current.second, shared_from_this());

        child->angle = angle;
        child->calc_h(end);
        children.push_back(child);
    }
    return children;
}

/*
branch 和 step 存在某种关联
关乎运算效率和成功率
 */

/*
运行速度慢，有很大一部分呢是因为输出log太多
*/