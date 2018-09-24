#ifndef PATHTESTER_INCLUDE
#define PATHTESTER_INCLUDE

#include <memory>

#include <cstdlib>
#include <ctime>

#include "pather.hpp"

class Pathtester {

private:
  int width, height;
  int diffMin, diffMax; // need to determine these if they arent set in constructor

  std::unique_ptr<grid_t> diffGrid;
  std::unique_ptr<map_t> pathMap;

public:

  Pathtester(int w, int h, node_func_t difficultyGen, int dMin = 0, int dMax = 0);

  static Pathtester FlatPathtester(int w, int h);
  static Pathtester RandomPathtester(int w, int h, int diffMin, int diffMax);

};

#endif //PATHTESTER_INCLUDE
