#include <iostream>
#include "pather.hpp"

/* Structure tests */

void drawGrid(grid_t& grid) {

  auto printNodes = [&grid](int x, int y, int& n) {

    // std::cout << "(" << x << ", " << y << ")"; // print grid coords

    if (y == grid.at(0).size() - 1) {
      std::cout << n << "\n";
    } else {
      std::cout << n;
    }
  };

  pather::forEachNode(grid, printNodes);
}

void drawMap(map_t& map) {

  auto w = 0;
  auto h = 0;
  
  for (auto& keyNode : map) {

    // get height and width by comparing for max keyNode.first, keyNode.second
  }

  auto prevGrid = std::make_unique<grid_t>(w, std::vector<index_t>(h));

  auto fillGrid = [&grid](int x, int y, int& n) {

                    grid.at(x).at(y) = map[index_t(x, y)];
  };
  
  pather::forEachNode(grid, fillGrid);
  
}

bool testGrid(std::vector<grid_t*>& grids) {

  std::cout << "Grid is " << flatGrid->size() << " elements wide and " <<
                                 flatGrid->at(0).size() << " elements tall\n";
  
  auto total = 0;
  auto totalDifficulty = [&total](int x, int y, int& n) {
    total += n;
  };

  pather::forEachNode(*flatGrid, totalDifficulty);
  std::cout << "Total of all node difficulties is " << total << "\n";

  if (total / flat != w * h) {
    std::cout << "FAULT: grid total difficulty does not match size\n";
  }

  std::cout << "Grid tests within limits\n";
  std::cout << "Attempting grid draw:\n";
  drawGrid(*flatGrid);
  return false;
}

int main(int argc, char** argv) {

  auto grids = std::vector<grid_t>();

  auto flat = 1;
  auto flatDifficulty = [flat](int x, int y, int& n) {
    n = flat;
  };

  auto w = 12;
  auto h = 24;
  std::unique_ptr<grid_t> flatGrid = pather::makeGrid(w, h, flatDifficulty);

  grids.push_back(flatGrid);
 
  testGrids(grids);

  std::cout << "Tests complete\n";
  return 0;
}
