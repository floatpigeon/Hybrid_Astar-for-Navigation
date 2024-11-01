#pragma once

#include <string>
#include <utility>
#include <vector>

const std::string RESET = "\033[0m";
const std::string BLACK = "\033[40m";
const std::string RED = "\033[41m";
const std::string GREEN = "\033[42m";
const std::string WHITE = "\033[47m";
const std::string BLUE = "\033[46m";

enum State { UNKNOW, EMPTY, OBSTACLE, CLOSED, OPEND, OBJECT, PATH, BEGIN, END };

class Map {
public:
  int row, col;

  Map(std::vector<std::vector<int>> num_map) : Num_map(num_map) {
    row = num_map.size();
    col = num_map[0].size();
  };

  std::vector<std::vector<State>> NumtoState();
  std::vector<std::vector<State>> StatetoGrid(int size);
  std::vector<std::vector<State>> NumtoGrid(int size);

  std::vector<std::vector<State>> getmap_State() { return State_map; }
  std::vector<std::vector<State>> getmap_Grid() { return Grid_map; }
  std::vector<std::vector<int>> getmap_int() { return Num_map; }

  void State_change(std::pair<int, int> position, State state);
  void updatePath_Statemap(std::vector<std::pair<int, int>> path);
  void updatePath_Gridmap(std::vector<std::pair<int, int>> path);
  void show();

private:
  int grid_size;
  std::vector<std::vector<int>> Num_map;
  std::vector<std::vector<State>> State_map;
  std::vector<std::vector<State>> Grid_map;
};