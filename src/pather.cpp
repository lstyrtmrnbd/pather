#include "pather.hpp"

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, std::function<int(int, int)> setDifficulty) {
  
  std::unique_ptr<grid_t> ugp(new std::vector<vector<int>>(w, std::vector<int>(h)));

  setEachNode(*ugp, setDifficulty);

  return ugp;
}

void pather::setEachNode(grid_t& grid, std::function<int(int, int)> nodeFunc) {

  for(auto x = grid.begin(); x != grid.end(); ++x) {

    for(auto y = x->begin(); y != x->end(); ++y) {

      *y = nodeFunc(x, y);  
    }
  }
}

map_t* pather::breadthFirst(const grid_t& grid) {


}
