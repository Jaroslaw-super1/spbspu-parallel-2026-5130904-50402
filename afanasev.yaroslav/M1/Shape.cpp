#include "Shape.hpp"

#include <algorithm>
#include <stdexcept>

namespace afanasev
{
  void Shape::extendBBox(double & minX, double & maxX, double & minY, double & maxY) const noexcept
  {
    minX = std::min(minX, x_ - r_);
    maxX = std::max(maxX, x_ + r_);
    minY = std::min(minY, y_ - r_);
    maxY = std::max(maxY, y_ + r_);
  }
}
