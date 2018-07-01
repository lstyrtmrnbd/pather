#include <iostream>
#include "pather.hpp"

/* Tangle out changes before executing */

int testGrid() {

  auto flatDifficulty = [](int, int) {
    return 1;
  };

  std::unique_ptr<grid_t> ugp = pather::makeGrid(12, 24, flatDifficulty);

  std::cout << "Grid is " << ugp->size() << " elements wide and " <<
                             ugp->at(0).size() << " elements tall.\n";
  
  return 1;
}

int main(int argc, char** argv) {

  testGrid();

  std::cout << "Tests finished.\n";

  return 0;
}
