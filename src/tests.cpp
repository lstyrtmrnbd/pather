#include <iostream>
#include "pather.hpp"

/* Tangle out changes and 'make pather' before executing */

int testGrid() {

  auto flatDifficulty = [](int x, int y, int& n) {
    n = 1;
  };

  std::unique_ptr<grid_t> ugp = pather::makeGrid(12, 24, flatDifficulty);

  std::cout << "Grid is " << ugp->size() << " elements wide and " <<
                             ugp->at(0).size() << " elements tall.\n";
  
  auto total = 0;

  auto totalDifficulty = [&total](int x, int y, int& n) {
    total += n;
  };

  pather::forEachNode(*ugp, totalDifficulty);

  std::cout << "Total of all node difficulties is " << total << "\n";

  return 0;
}

int main(int argc, char** argv) {

  testGrid();

  std::cout << "Tests finished.\n";

  return 0;
}
