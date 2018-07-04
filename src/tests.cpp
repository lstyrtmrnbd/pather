#include <iostream>
#include <memory>
#include <utility> // std::move
#include "pather.hpp"

// map realized as grid for drawing etc
using prev_grid_t = std::vector<std::vector<index_t>>;

void drawGrid(grid_t& grid) {

  auto printNodes = [&grid](int x, int y, int& n) {

    // std::cout << "(" << x << ", " << y << ")"; // print grid coords

    if (y == grid.at(0).size() - 1) {
      std::cout << n << "\n";
    } else {
      std::cout << n;
    }
  };

  forVec2D<int>(grid, printNodes);
}

void drawMap(map_t& map) {

  auto w = 0;
  auto h = 0;
  
  for (auto& keyNode : map) {

    // get height and width by comparing for max keyNode.first, keyNode.second
  }

  auto prevGrid = std::make_unique<prev_grid_t>(w, std::vector<index_t>(h));

  auto fillGrid = [&prevGrid, &map](int x, int y, index_t& n) {

    // puts the value of previous node in path map into grid
    n = map[index_t(x, y)];
  };
  
  forVec2D<index_t>(*prevGrid, fillGrid); // templated!
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
    
    std::cout << "Attempting grid draw:\n";
    drawGrid(*grid);
  }

  std::cout << "Grid tests within limits\n";
}

int main(int argc, char** argv) {

  auto grids = makeGrids();
  
  testGrids(*grids);

  std::cout << "Tests complete\n";
  return 0;
}
