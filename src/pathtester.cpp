#include "pathtester.hpp"

Pathtester::Pathtester(int w, int h, node_func_t difficultyGen, int dMin, int dMax)
  : width(w), height(h), diffMin(dMin), diffMax(dMax) {

  diffGrid = pather::makeGrid(w, h, difficultyGen);
}


Pathtester Pathtester::FlatPathtester(int w, int h) {

  auto flat = 1;
  auto flatDifficulty = [flat](int x, int y, int& n) {
    n = flat;
  };

  return Pathtester(w, h, flatDifficulty, flat, flat);
}

Pathtester Pathtester::RandomPathtester(int w, int h, int diffMin, int diffMax) {

  int range = diffMax - diffMin;
  std::srand((int) std::time(0));
  auto randDifficulty = [range, diffMin](int x, int y, int& n){
                          
    n = (std::rand() % range) + diffMin;
  };

  return Pathtester(w, h, randDifficulty, diffMin, diffMax);
}

std::pair<int, int> Pathtester::getDimensions() {

  return std::make_pair(this->width, this->height);
}

int Pathtester::getDifficulty(int x, int y) {

  return this->diffGrid->at(x).at(y);
}

double Pathtester::getRelativeDifficulty(int x, int y) {

  int diff = getDifficulty(x, y);
  
  if (diff < this->diffMin) {
    return 0.0;

  } else if (diff > this->diffMax) {
    return 1.0;
    
  } else {
    return  (double)(diff - this->diffMin) / (double)(this->diffMax - this->diffMin);
  }
}
