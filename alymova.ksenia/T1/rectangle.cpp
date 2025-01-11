#include "rectangle.hpp"
#include <stdexcept>
alymova::Rectangle::Rectangle(point_t p1, point_t p2):
  low_left_(p1),
  upp_right_(p2),
  frame_rect_()
{
  if (p2 < p1)
  {
    throw std::logic_error("Incorrect description rectangle");
  }
  double width = upp_right_.x - low_left_.x;
  double height = upp_right_.y - low_left_.y;
  point_t pos = {(low_left_.x + width / 2.0), (upp_right_.y - height / 2.0)};
  frame_rect_ = rectangle_t{width, height, pos};
}
double alymova::Rectangle::getArea() const noexcept
{
  double width = frame_rect_.width;
  double height = frame_rect_.height;
  return width * height;
}
alymova::rectangle_t alymova::Rectangle::getFrameRect() const noexcept
{
  return frame_rect_;
}
void alymova::Rectangle::move(double shift_x, double shift_y) noexcept
{
  point_t shift_point{shift_x, shift_y};
  low_left_ += shift_point;
  upp_right_ += shift_point;
  alymova::moveFrameRect(frame_rect_, shift_x, shift_y);
}
void alymova::Rectangle::move(point_t point) noexcept
{
  point_t pos = {frame_rect_.pos};
  double shift_x = point.x - pos.x;
  double shift_y = point.y - pos.y;
  move(shift_x, shift_y);
}
void alymova::Rectangle::unsafeScale(double ratio) noexcept
{
  double width = frame_rect_.width;
  double height = frame_rect_.height;
  low_left_ += (point_t{0.5 * (width - ratio * width), 0.5 * (height - ratio * height)});
  upp_right_ += (point_t{0.5 * (ratio * width - width), 0.5 * (ratio * height - height)});
  alymova::scaleFrameRect(frame_rect_, ratio);
}
alymova::Shape* alymova::Rectangle::clone() const
{
  Rectangle* rect = nullptr;
  try
  {
    rect = new Rectangle(low_left_, upp_right_);
    Shape* shape = rect;
    return shape;
  }
  catch (const std::bad_alloc& e)
  {
    delete rect;
    throw;
  }
}
