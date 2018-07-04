#include "pather.hpp"

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, node_func_t setDifficulty) {
  
  auto ugp = std::make_unique<grid_t>(w, std::vector<int>(h));

  forVec2D<int>(*ugp, setDifficulty);

  return ugp;
}

bool pather::inGridBounds(const grid_t& grid, index_t index) {

  if (index.first > (signed)grid.size() || index.first < 0) return false;
  
  if (index.second > (signed)grid[0].size() || index.second < 0) return false;

  return true;
}

std::unique_ptr<path_t> pather::listNeighbors(const grid_t& grid, index_t index) {

  auto neighbors = std::make_unique<path_t>();
  
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

  auto frontier = std::make_unique<std::queue<index_t>>();
  frontier->push(start);

  auto ump = std::make_unique<map_t>();
  ump->insert(std::pair<index_t, index_t>(start, start));

  while (!frontier->empty()) {
    
    index_t current = frontier->front();
    frontier->pop();

    auto neighbors = listNeighbors(grid, current);
    for (auto next : *neighbors) {

      if (ump->find(next) == ump->end()) {
	frontier->push(next);
	ump->insert(std::pair<index_t, index_t>(next, current));
      }
    }
  }  
  return ump;
}
