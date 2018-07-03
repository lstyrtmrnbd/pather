#include <iostream>
#include "pather.hpp"

/* Structure tests */

void drawGrid(grid_t& grid) {

  auto printNodes = [&grid](int x, int y, int& n) {

    // std::cout << "(" << x << ", " << y << ")";

    if (y == grid.at(0).size() - 1) {
      std::cout << n << "\n";
    } else {
      std::cout << n;
    }
  };

  pather::forEachNode(grid, printNodes);
}

bool testGrid() {

  auto flat = 1;
  auto flatDifficulty = [flat](int x, int y, int& n) {
    n = flat;
  };

  auto w = 12;
  auto h = 24;
  std::unique_ptr<grid_t> flatGrid = pather::makeGrid(w, h, flatDifficulty);
  std::cout << "flatGrid is " << flatGrid->size() << " elements wide and " <<
                                 flatGrid->at(0).size() << " elements tall\n";
  
  auto total = 0;
  auto totalDifficulty = [&total](int x, int y, int& n) {
    total += n;
  };

  pather::forEachNode(*flatGrid, totalDifficulty);
  std::cout << "Total of all node difficulties is " << total << "\n";

  if (total / flat != w * h) {
    std::cout << "flatGrid total difficulty does not match size\n";
    return true;
  }

  std::cout << "Grid tests within limits\n";
  std::cout << "Attempting grid draw:\n";
  drawGrid(*flatGrid);
  return false;
}

int main(int argc, char** argv) {

  testGrid();

  std::cout << "Tests complete\n";
  return 0;
}
