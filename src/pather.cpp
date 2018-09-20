#include "pather.hpp"
// DEBUG
#include <thread>
#include <chrono>

std::unique_ptr<grid_t> pather::makeGrid(int w, int h, node_func_t setDifficulty) {
  
  auto ugp = std::make_unique<grid_t>(w, std::vector<int>(h));

  forVec2D<int>(*ugp, setDifficulty);

  return ugp;
}

std::string pather::indexToString(index_t& index) {

  auto out = std::string();

  out = out + "(" + std::to_string(index.first) + ", " + std::to_string(index.second) + ")";
  
  return out;
}

// finds the sequence of indexes leading to the start of the map from specified point
std::unique_ptr<path_t> pather::findPath(const map_t& map, index_t end) {

  // return wrapped nullptr if end point doesn't exist in map
  if(map.find(end) == map.end()) return std::unique_ptr<path_t>(nullptr);
  
  auto path = std::make_unique<path_t>();
  
  auto current = end;
  auto prev = map.at(current);

  // start index is mapped to itself
  while (prev != current) {

    path->push_back(current);
    current = prev;
    prev = map.at(current);
  }

  path->push_back(current);
 
  return path;
}

// could be a more general test for validity that accounts for passability
bool pather::inGridBounds(const grid_t& grid, index_t index) {

  int w = static_cast<int>(grid.size());
  int h = static_cast<int>(grid[0].size()); // assumes all inner vectors are the same size as the first
  
  if (index.first < 0 || index.second < 0) return false;
  if (index.first >= w || index.second >= h) return false;

  return true;
}

// generate list of Von Neumann neighborhood, rather explicitly
std::unique_ptr<path_t> pather::listNeighborsVonNeumann(const grid_t& grid, index_t index) {

  auto neighbors = std::make_unique<path_t>();
  
  auto N = index_t(index.first, index.second + 1);
  auto E = index_t(index.first + 1, index.second);
  auto S = index_t(index.first, index.second - 1);
  auto W = index_t(index.first - 1, index.second);

  if (inGridBounds(grid, N)) neighbors->push_back(N);
  if (inGridBounds(grid, E)) neighbors->push_back(E);
  if (inGridBounds(grid, S)) neighbors->push_back(S);
  if (inGridBounds(grid, W)) neighbors->push_back(W);

  return neighbors;
}

// generate list of Moore neighborhood
std::unique_ptr<path_t> pather::listNeighborsMoore(const grid_t& grid, index_t index) {

  auto neighbors = std::make_unique<path_t>();

  for (int x = -1; x < 2; ++x) {
    for (int y = -1; y < 2; ++y) {
      auto candidate = index_t(index.first + x, index.second + y);

      if (inGridBounds(grid, candidate) && candidate != index) neighbors->push_back(candidate);
    }
  }

  return neighbors;
}

// explores all nodes equally, no account for difficulty values
std::unique_ptr<map_t> pather::breadthFirst(const grid_t& grid, index_t start) {

  auto frontier = std::make_unique<std::queue<index_t>>();
  frontier->push(start);

  auto previousMap = std::make_unique<map_t>();
  previousMap->insert(std::pair<index_t, index_t>(start, start));

  while (!frontier->empty()) {
    
    index_t current = frontier->front();
    frontier->pop();

    auto neighbors = listNeighborsVonNeumann(grid, current);
    for (auto next : *neighbors) {

      if (previousMap->find(next) == previousMap->end()) {
	frontier->push(next);
	previousMap->insert(std::pair<index_t, index_t>(next, current));
      }
    }
  }
  std::cout << "breadthFirst filled a map with " << previousMap->size() << " keys\n";
  return previousMap;
}

// closer to Uniform Cost Search, called dijkstra for historical considerations
std::unique_ptr<map_t> pather::dijkstra(const grid_t& grid, index_t start) {

  // comparator function so lower cost nodes are returned first from priority queue
  auto costGreater = [](const cost_t& a, const cost_t& b) {

    return a.second > b.second;
  };
  
  auto frontier = std::make_unique<std::priority_queue<cost_t,
						       std::vector<cost_t>,
						       std::function<bool(cost_t, cost_t)>>>(costGreater);
  frontier->push(cost_t(start, 0));

  auto costSoFar = std::make_unique<total_cost_t>();
  costSoFar->insert(std::pair<index_t, int>(start, 0));
  
  auto previousMap = std::make_unique<map_t>();
  previousMap->insert(std::pair<index_t, index_t>(start, start));

  while (!frontier->empty()) {

    index_t current = frontier->top().first;
    frontier->pop();

    std::cout << "Currently considering " << indexToString(current) << "\n";
    
    // early exit for current == goal would go here

    auto neighbors = listNeighborsVonNeumann(grid, current);
    for (auto next : *neighbors) {

      int newCost = costSoFar->at(current) + grid.at(next.first).at(next.second);

      std::cout << "Cost of moving to " << indexToString(next) << " is " << std::to_string(newCost) << "\n";

      std::this_thread::sleep_for(std::chrono::seconds(1));
      
      if (costSoFar->find(next) == costSoFar->end() || costSoFar->at(next) < newCost) {

	(*costSoFar)[next] = newCost;
	frontier->push(cost_t(next, newCost));
	previousMap->insert(std::pair<index_t, index_t>(next, current));	
      }
    }
  }
  
  return  previousMap;
}
