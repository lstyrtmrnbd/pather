#include "pather.hpp"

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, node_func_t setDifficulty) {
  
  std::unique_ptr<grid_t> ugp(new std::vector<std::vector<int>>(w, std::vector<int>(h)));

  forEachNode(*ugp, setDifficulty);

  return ugp;
}

void pather::forEachNode(grid_t& grid, node_func_t nodeFunc) {

  auto x = 0, y = 0;

  for(auto ix = grid.begin(); ix != grid.end(); ++ix) {

    for(auto iy = ix->begin(); iy != ix->end(); ++iy) {

      nodeFunc(x, y, *iy);
      y += 1;  
    }
    x += 1;
  }
}

std::unique_ptr<map_t> pather::breadthFirst(const grid_t& grid, index_t start) {

  std::queue<index_t> frontier();
  frontier.push(start);

  std::unique_ptr<map_t> ump(new map_t());
  ump->insert(std::pair<index_t, index_t>(start, start));

  while (!frontier.empty()) {

    index_t current = frontier.pop(); 
  }
  

  return ump;
}
