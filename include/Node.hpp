#pragma once

#include <Eigen/Dense>
#include <memory>
#include <utility>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    Node(float x, float y, std::shared_ptr<Node> parent) : angle(0), x_(x), y_(y), parent(parent) {
        calc_g();
        value_h_ = 0;
    }

    const std::shared_ptr<Node> parent;
    std::pair<float, float> site() const;

    float value_f() const;

    std::vector<std::shared_ptr<Node>> GenerateChildren(float step, std::pair<float, float>& end);

    double get_h() { return value_h_; }
    double get_g() { return value_g_; }
    float calc_h(std::pair<float, float>& end, int type = 1);
    float angle;

private:
    float calc_g();
    float x_, y_;
    float value_g_, value_h_;
};

class GreaterNode {
public:
    bool operator()(std::shared_ptr<Node>& self, std::shared_ptr<Node>& other) const {
        return self->value_f() > other->value_f();
    }
};
