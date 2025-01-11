#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"
#include "regular.hpp"
namespace alymova
{
  struct Circle final: public Shape
  {
  public:
    Circle(point_t pos, double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double shift_x, double shift_y) noexcept override;
    void move(point_t point) noexcept override;
    void unsafeScale(double ratio) noexcept override;
    Shape* clone() const override;
  protected:
    point_t pos_;
    double radius_;
    Regular regular_;
  };
}
#endif
