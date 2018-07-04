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
      y += 1;
    }

    x += 1;
  }
}

#endif // FORVEC2D_INCLUDE
