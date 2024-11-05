#pragma once

#include <memory>
#include <utility>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    Node(float x, float y, std::shared_ptr<Node> parent) : x(x), y(y), parent(parent) {
        calc_g();
        value_h = 0;
    }

    std::shared_ptr<Node> parent;
    std::pair<float, float> site() const;

    float value_f() const;
    bool operator>(const Node& other) const { return value_f() > other.value_f(); }

    std::vector<std::shared_ptr<Node>> GenerateChildren(float step, std::pair<float, float>& end);

private:
    float calc_g();
    float calc_h(std::pair<float, float> end, int type = 0);
    float x, y;
    float value_g, value_h;
};
