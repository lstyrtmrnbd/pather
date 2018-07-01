#ifndef PATHER_INCLUDE
#define PATHER_INCLUDE
#include <functional>
#include <map>
#include <memory>
#include <vector>

using grid_t = std::vector<std::vector<int>>;
using map_t = std::map<std::pair<int, int>, std::pair<int, int>>;
using path_t = std::vector<std::pair<int, int>>;

namespace pather {

  std::unique_ptr<grid_t> makeGrid(int w, int h, std::function<int(int, int)> setDifficulty);
  void setEachNode(grid_t& grid, std::function<int(int, int)> nodeFunc);

  path_t* findPath(const map_t& map); 
  map_t* breadthFirst(const grid_t& grid);
  map_t* dijkstras(const grid_t& grid);
}

#endif // PATHER_INCLUDE
