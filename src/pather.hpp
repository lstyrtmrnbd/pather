#ifndef PATHER_INCLUDE
#define PATHER_INCLUDE
#include <functional>
#include <iostream> // error checking
#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "forvec2d.hpp"

// location in a grid
using index_t = std::pair<int, int>;

// grid of difficulty values
using grid_t = std::vector<std::vector<int>>;

// used for mapping an index to its path predecessor
using map_t = std::map<index_t, index_t>;

// sequence of locations
using path_t = std::vector<index_t>;

// function type that is executed on each grid node during iteration,
// used in grid construction so difficulty generation can be arbitrarily parameterized
using node_func_t = std::function<void(int, int, int&)>;

// pairing of a location and the dynamic cost to reach it
// used as values in queue to prioritize cheaper paths
using cost_t = std::pair<index_t, int>;

// mapping of a node to the dynamic total cost to reach it
using total_cost_t = std::map<index_t, int>;

namespace pather {

  bool inGridBounds(const grid_t& grid, index_t index);
  std::unique_ptr<grid_t> makeGrid(int w, int h, node_func_t setDifficulty);

  std::unique_ptr<path_t> listNeighborsVonNeumann(const grid_t& grid, index_t index);
  std::unique_ptr<path_t> listNeighborsMoore(const grid_t& grid, index_t index);
  std::unique_ptr<path_t> findPath(const map_t& map, index_t end); 
  
  std::unique_ptr<map_t> breadthFirst(const grid_t& grid, index_t start);
  std::unique_ptr<map_t> dijkstra(const grid_t& grid, index_t start);
}

#endif // PATHER_INCLUDE
