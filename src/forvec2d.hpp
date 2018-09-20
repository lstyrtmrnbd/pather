#ifndef FORVEC2D_INCLUDE
#define FORVEC2D_INCLUDE
#include <functional>
#include <vector>

/**
 * Iterate through a 2D vector and apply a function with access
 * to the x,y indices to each element
 */

template<typename T>
void forVec2D(std::vector<std::vector<T>>& vec2D,
	      std::function<void(int, int, T&)> elementFunc) {

  auto x = 0;
  for (auto ix = vec2D.begin(); ix != vec2D.end(); ++ix) {

    auto y = 0;
    for (auto iy = ix->begin(); iy != ix->end(); ++iy) {

      elementFunc(x, y, *iy);
      ++y;
    }

    ++x;
  }
}

/**
 * Iterate through a 2D vector and apply a function,
 * but with the inner vector as the outer iterator
 *
 * !Makes the assumption that all inner vectors are the same length as the first!
 */

template<typename T>
void forVec2DInner(std::vector<std::vector<T>>& vec2D,
		   std::function<void(int, int, T&)> elementFunc) {

  for (auto y = 0; y < vec2D.at(0).size(); ++y) {

    for (auto x = 0; x < vec2D.size(); ++x) {

      elementFunc(x, y, vec2D.at(x).at(y));
    }
  }
}
#endif // FORVEC2D_INCLUDE
