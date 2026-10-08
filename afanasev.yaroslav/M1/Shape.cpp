#include "Shape.hpp"

#include <algorithm>
#include <stdexcept>

namespace afanasev
{
  Shape::Shape(long long r, long long, long long cx, long long cy)
  {
    r_ = static_cast< double >(r);
    x_ = static_cast< double >(cx);
    y_ = static_cast< double >(cy);
  }

  void Shape::extendBBox(double & minX, double & maxX, double & minY, double & maxY) const noexcept
  {
    minX = std::min(minX, x_ - r_);
    maxX = std::max(maxX, x_ + r_);
    minY = std::min(minY, y_ - r_);
    maxY = std::max(maxY, y_ + r_);
  }

  bool Shape::contains(double px, double py) const noexcept 
  {
    const double dx = px - x_;
    const double dy = py - y_;
    return dx * dx + dy * dy <= r_ * r_;
  }
}
