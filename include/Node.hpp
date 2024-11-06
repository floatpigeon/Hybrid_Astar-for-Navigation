#pragma once

#include <Eigen/Dense>
#include <memory>
#include <utility>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    Node(float x, float y, std::shared_ptr<Node> parent) : x_(x), y_(y), parent(parent) {
        calc_g();
        value_h_ = 0;
    }

    const std::shared_ptr<Node> parent;
    std::pair<float, float> site() const;

    float value_f() const;

    std::vector<std::shared_ptr<Node>> GenerateChildren(float step, std::pair<float, float>& end);

private:
    float calc_g();
    float calc_h(std::pair<float, float> end, int type = 0);
    float x_, y_;
    float value_g_, value_h_;
};

class GreaterNode {
public:
    bool operator()(std::shared_ptr<Node>& self, std::shared_ptr<Node>& other) const {
        return self->value_f() > other->value_f();
    }
};
