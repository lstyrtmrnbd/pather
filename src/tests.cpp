#include <iostream>
#include <functional>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "pather.hpp"

// map realized as grid for drawing etc
using prev_grid_t = std::vector<std::vector<index_t>>;

// function type of map generating path finding functions
using map_function_t = std::function<std::unique_ptr<map_t>(const grid_t&, index_t)>;

using shape_row_t = std::vector<std::unique_ptr<sf::Shape>>;
using shapes_t = std::vector<std::unique_ptr<shape_row_t>>;

const int winWidth = 800;
const int winHeight = 600;

std::unique_ptr<sf::RenderWindow> window;
std::unique_ptr<shapes_t> shapes;

sf::Color cellColor = sf::Color(0, 255, 0);

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

  // puts the value of previous node in path map into grid
  auto fillGrid = [&prevGrid, &map](int x, int y, index_t& n) {
    auto key = index_t(x, y);
    n = map.at(key);
  };
  
  forVec2D<index_t>(*prevGrid, fillGrid); // templated!

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

void fillCells(int w, int h) {

  shapes = std::make_unique<shapes_t>(w, std::vector<std::unique_ptr<sf::Shape>>(h));
  
  float cellw = winWidth / (float)w;
  float cellh = winHeight / (float)h;
  
  auto fill = [cellw, cellh](int x, int y, std::unique_ptr<sf::Shape>& shape) {

    shape.reset(new sf::RectangleShape(sf::Vector2f(cellw, cellh)));

    shape->setFillColor(cellColor);

    shape->setPosition((float)x * cellw, (float)y * cellh);
  };

  forVec2D<std::unique_ptr<sf::Shape>>(*shapes, fill);
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

void testMappingFunction(const grid_t& grid, index_t start, index_t end, map_function_t func) {

  std::cout << "Mapping and then extracting path from " << pather::indexToString(start) << " to " << pather::indexToString(end) << "\n";
  auto prevMap = func(grid, start);

  drawMap(*prevMap);

  auto path = pather::findPath(*prevMap, end);

  std::cout << "Path:\n";
  for (auto i = path->begin(); i != path->end(); ++i) {

    std::cout << pather::indexToString(*i) << " ";
  }
  std::cout << "\n";
}

void testNeighbors(const grid_t& grid, index_t index) {

  auto neighbors = pather::listNeighborsMoore(grid, index);

  for (auto& neighbor : *neighbors) {
    std::cout << pather::indexToString(neighbor) << " ";
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
    testMappingFunction(*grid, index_t(3, 3), index_t(9, 9), pather::breadthFirst);

    std::cout << "Testing dijkstra on grid:\n";
    testMappingFunction(*grid, index_t(3, 3), index_t(9, 9), pather::dijkstra);
    
    std::cout << "Moore neighbors of (3, 3) are ";
    testNeighbors(*grid, index_t(3, 3));
    std::cout << "\n";
  }

  std::cout << "Grid tests within limits\n";
}

int main(int argc, char** argv) {

  auto grids = makeGrids();
  
  //testGrids(*grids);

  //std::cout << "Tests complete\n";

  window = std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight), "testing pather");

  fillCells(8,6);

  auto drawShape = [](int x, int y, std::unique_ptr<sf::Shape>& shape){

    window->draw(*shape);
  };
  
  while (window->isOpen()) {

    sf::Event event;

    while (window->pollEvent(event)) {
    
      if (event.type == sf::Event::Closed)
	window->close();
    }
    
    window->clear(sf::Color::Black);
    
    forVec2D<std::unique_ptr<sf::Shape>>(*shapes, drawShape);
    
    window->display();
  }
  
  return 0;
}
