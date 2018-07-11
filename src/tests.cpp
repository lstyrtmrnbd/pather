#include <iostream>
#include <memory>
#include <string>
#include "pather.hpp"

// map realized as grid for drawing etc
using prev_grid_t = std::vector<std::vector<index_t>>;

std::string indexToString(index_t index) {

  auto out = std::string();

  out = out + "(" + std::to_string(index.first) + ", " + std::to_string(index.second) + ")";
  
  return out;
}

std::unique_ptr<prev_grid_t> makePrevGrid(const map_t& map) {

  auto w = 0;
  auto h = 0;
  
  for (auto kvPair : map) {

    auto x = kvPair.first.first;
    auto y = kvPair.first.second;
    
    if (x > w) w = x;
    if (y > h) h = y;
  }

  auto prevGrid = std::make_unique<prev_grid_t>(w, std::vector<index_t>(h));

  auto failedKeys = 0; //ec

  // puts the value of previous node in path map into grid
  // using [] operator can insert if key doesn't exist; map is const, use .at()
  auto fillGrid = [&prevGrid, &map, &failedKeys](int x, int y, index_t& n) {

    auto key = index_t(x, y);
    
    try {
      n = map.at(key);
    } catch (const std::out_of_range& oor) {
      // std::cerr << "OOR Error: " << oor.what() << " ";
      std::cout << indexToString(key) << " ";
      failedKeys += 1;
    }
  };
  
  forVec2D<index_t>(*prevGrid, fillGrid); // templated!

  std::cout << "prevGrid made, with " << failedKeys << " failed keys\n";
  return prevGrid;
}

void drawGrid(grid_t& grid) {

  auto printNodes = [&grid](int x, int y, int& n) {

    std::cout << n;
    if (x == grid.size() - 1) std::cout << std::endl;
  };

  forVec2DInner<int>(grid, printNodes);
}

void drawPrevGrid(prev_grid_t& grid) {

  auto printNodes = [&grid](int x, int y, index_t& n) {

    if (n.first != x) {
      std::cout << "-";
    } else if (n.second != y) {
      std::cout << "|";
    }
    if (x == grid.size() - 1) std::cout << std::endl;
  };

  forVec2DInner<index_t>(grid, printNodes);
}

void drawMap(const map_t& map) {

  auto prevGrid = makePrevGrid(map);

  drawPrevGrid(*prevGrid);
}

std::unique_ptr<std::vector<std::unique_ptr<grid_t>>> makeGrids() {

  auto grids = std::make_unique<std::vector<std::unique_ptr<grid_t>>>();

  auto flat = 1;
  auto flatDifficulty = [flat](int x, int y, int& n) {
    n = flat;
  };

  auto w = 12;
  auto h = 24;
  
  grids->push_back(pather::makeGrid(w, h, flatDifficulty));

  return grids;
}

void testBreadthFirst(const grid_t& grid, index_t start, index_t end) {

  std::cout << "breadthFirst from " << indexToString(start) << " to " << indexToString(end) << "\n";
  auto prevMap = pather::breadthFirst(grid, start);

  drawMap(*prevMap);

  auto path = pather::findPath(*prevMap, end);

  std::cout << "Path:\n";
  for (auto i = path->begin(); i != path->end(); ++i) {

    std::cout << indexToString(*i) << " ";
  }
  std::cout << "\n";
}

void testNeighbors(const grid_t& grid, index_t index) {

  auto neighbors = pather::listNeighborsMoore(grid, index);

  for (auto& neighbor : *neighbors) {
    std::cout << indexToString(neighbor) << " ";
  }
}

void testGrids(std::vector<std::unique_ptr<grid_t>>& grids) {

  for (auto& grid : grids) {

    std::cout << "Grid is " << grid->size() << " elements wide and " <<
                                 grid->at(0).size() << " elements tall\n";
  
    auto total = 0;
    auto totalDifficulty = [&total](int x, int y, int& n) {
      total += n;
    };

    forVec2D<int>(*grid, totalDifficulty);
    std::cout << "Total of all node difficulties is " << total << "\n";

    /* Actual per grid tests go here */
    
    std::cout << "Drawing grid difficulties:\n";
    drawGrid(*grid);

    std::cout << "Testing breadthFirst on grid:\n";
    testBreadthFirst(*grid, index_t(3, 3), index_t(9, 9));

    std::cout << "Moore neighbors of (3, 3) are ";
    testNeighbors(*grid, index_t(3, 3));
    std::cout << "\n";
  }

  std::cout << "Grid tests within limits\n";
}

int main(int argc, char** argv) {

  auto grids = makeGrids();
  
  testGrids(*grids);

  std::cout << "Tests complete\n";
  return 0;
}
