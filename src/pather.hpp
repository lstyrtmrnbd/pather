#ifndef PATHER_INCLUDE
#define PATHER_INCLUDE
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>

using index_t = std::pair<int, int>;
using grid_t = std::vector<std::vector<int>>;
using map_t = std::map<index_t, index_t>;
using path_t = std::vector<index_t>;
using node_func_t = std::function<void(int, int, int&)>;

namespace pather {

  std::unique_ptr<grid_t> makeGrid(int w, int h, node_func_t setDifficulty);
  void forEachNode(grid_t& grid, node_func_t nodeFunc);

  bool inGridBounds(const grid_t& grid, index_t index);

  std::unique_ptr<path_t> listNeighbors(const grid_t& grid, index_t index);

  std::unique_ptr<map_t> breadthFirst(const grid_t& grid, index_t start);
  std::unique_ptr<map_t> dijkstras(const grid_t& grid);

  std::unique_ptr<path_t> findPath(const map_t& map); 
}

#endif // PATHER_INCLUDE
