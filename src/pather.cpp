#include "pather.hpp"

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, node_func_t setDifficulty) {
  
  std::unique_ptr<grid_t> ugp(new std::vector<std::vector<int>>(w, std::vector<int>(h)));

  forEachNode(*ugp, setDifficulty);

  return ugp;
}

void pather::forEachNode(grid_t& grid, node_func_t nodeFunc) {

  auto x = 0;
  for (auto ix = grid.begin(); ix != grid.end(); ++ix) {

    auto y = 0;
    for (auto iy = ix->begin(); iy != ix->end(); ++iy) {
      
      nodeFunc(x, y, *iy);
      y += 1;  
    }
    
    x += 1;
  }
}

bool pather::inGridBounds(const grid_t& grid, index_t index) {

  if (index.first > (signed)grid.size() || index.first < 0) return false;
  
  if (index.second > (signed)grid[0].size() || index.second < 0) return false;

  return true;
}

std::unique_ptr<path_t> pather::listNeighbors(const grid_t& grid, index_t index) {

  std::unique_ptr<path_t> neighbors(new path_t());
  
  auto N = index_t(index.first, index.second++);
  auto E = index_t(index.first++, index.second);
  auto S = index_t(index.first, index.second--);
  auto W = index_t(index.first--, index.second);

  if (inGridBounds(grid, N)) neighbors->push_back(N);
  if (inGridBounds(grid, E)) neighbors->push_back(E);
  if (inGridBounds(grid, S)) neighbors->push_back(S);
  if (inGridBounds(grid, W)) neighbors->push_back(W);

  return neighbors;
}

std::unique_ptr<map_t> pather::breadthFirst(const grid_t& grid, index_t start) {

  std::queue<index_t> frontier = std::queue<index_t>();
  frontier.push(start);

  std::unique_ptr<map_t> ump(new map_t());
  ump->insert(std::pair<index_t, index_t>(start, start));

  while (!frontier.empty()) {
    
    index_t current = frontier.front();
    frontier.pop();

    for (auto next : *listNeighbors(grid, current)) {

      if (ump->find(next) == ump->end()) {
	frontier.push(next);
	ump->insert(std::pair<index_t, index_t>(next, current));
      }
    }
  }  
  return ump;
}
