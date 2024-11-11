#pragma once

#include <Eigen/Dense>
#include <memory>
#include <utility>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    Node(float x, float y, std::pair<float, float>& end, std::shared_ptr<Node> parent)
        : x_(x), y_(y), parent(parent) {
        calc_g();
        calc_h(end);
        value_h_ = 0;
    }
    const std::shared_ptr<Node> parent;

    std::pair<float, float> site() const { return {x_, y_}; }
    float value_f() const { return value_g_ + value_h_; }

    float get_h() { return value_h_; }
    float get_g() { return value_g_; }
    float get_angle() { return angle; }

    std::vector<std::shared_ptr<Node>> GenerateChildren(float step, std::pair<float, float>& end);

private:
    float calc_g();
    float calc_h(std::pair<float, float> end, int type = 0);
    float x_, y_;
    float value_g_, value_h_;
    float angle = 0;
};

class GreaterNode {
public:
    bool operator()(std::shared_ptr<Node>& self, std::shared_ptr<Node>& other) const {
        return self->value_f() > other->value_f();
    }
};
