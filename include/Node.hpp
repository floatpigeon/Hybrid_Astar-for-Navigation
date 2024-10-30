#pragma once

class Node {
public:
  int x, y;
  float value_g, value_h;
  Node *parent;

  Node(int x, int y, int g = 0, int h = 0, Node *parent = nullptr)
      : x(x), y(y), value_g(g), value_h(h), parent(parent) {}

  float value_f() const { return value_h + value_g; }

  bool operator>(const Node &other) const {
    return value_f() > other.value_f();
  }
};
