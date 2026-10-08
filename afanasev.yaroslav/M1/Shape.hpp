#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace afanasev
{

  class Shape
  {
  public:
    void extendBBox(double & minX, double & maxX, double & minY, double & maxY) const noexcept;

  private:
    double r_ = 0.0;
    double x_ = 0.0;
    double y_ = 0.0;
  };
}

#endif
