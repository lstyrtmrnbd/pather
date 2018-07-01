#include "pather.hpp"

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, std::function<int(int, int)> setDifficulty) {
  
  std::unique_ptr<grid_t> ugp(new std::vector<std::vector<int>>(w, std::vector<int>(h)));

  setEachNode(*ugp, setDifficulty);

  return ugp;
}

void pather::setEachNode(grid_t& grid, std::function<int(int, int)> nodeFunc) {

  int x = 0;
  int y = 0;

  for(auto ix = grid.begin(); ix != grid.end(); ++ix) {

    for(auto iy = ix->begin(); iy != ix->end(); ++iy) {

      *iy = nodeFunc(x, y);
      y += 1;  
    }
    
    x += 1;
  }
}
/**
map_t* pather::breadthFirst(const grid_t& grid) {


}
*/
