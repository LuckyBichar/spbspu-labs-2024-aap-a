#include "regular.hpp"
#include <cmath>
#include <stdexcept>

namespace
{
  bool compareDoubles(const double first, const double second)
  {
    return std::fabs(first - second) > 0.0001;
  }

  double getDist(const tkach::point_t& point1, const tkach::point_t& point2)
  {
    return std::sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
  }

  bool isEqualPoints(const tkach::point_t& point1, const tkach::point_t& point2)
  {
    return point1.x == point2.x && point1.y == point2.y;
  }
}

size_t tkach::Regular::getSideAmount() const
{
  const double res = std::acos(-1.0) / (std::acos(getDist(first_point_, third_point_) / getDist(first_point_, second_point_)));
  size_t round_res = std::round(res);
  return compareDoubles(res, std::round(res)) ? 0 : round_res;
}

tkach::Regular::Regular(const point_t& first_point, const point_t& second_point, const point_t& third_point):
  first_point_(first_point),
  second_point_(second_point),
  third_point_(third_point)
{
  if (getDist(first_point, third_point) > getDist(first_point, second_point))
  {
    std::swap(second_point_, third_point_);
  }
  double first_side = getDist(first_point_, second_point_);
  double second_side = getDist(third_point_, second_point_);
  double third_side = getDist(first_point_, third_point_);
  if (compareDoubles(first_side * first_side, second_side * second_side + third_side * third_side))
  {
    throw std::logic_error("Triangle is not right");
  }
  if (isEqualPoints(first_point, second_point) || isEqualPoints(first_point, third_point) || isEqualPoints(third_point, second_point))
  {
    throw std::logic_error("Triangle doesn`t exist");
  }
  if (getSideAmount() < 3)
  {
    throw std::logic_error("Shape doesn`t exist");
  }
}

tkach::Shape* tkach::Regular::clone() const
{
  return new Regular(*this);
}

double tkach::Regular::getArea() const
{
  return (getSideAmount() * getDist(second_point_, third_point_) * getDist(first_point_, third_point_));
}

tkach::rectangle_t tkach::Regular::getFrameRect() const
{
  point_t start_point = second_point_;
  const double step_angle = 2.0 * std::acos(-1.0) / getSideAmount();
  double top = start_point.y;
  double bot = start_point.y;
  double left = start_point.x;
  double right = start_point.x;
  point_t new_point = {start_point.x + 1, start_point.y + 1};
  point_t start_point_temp = start_point;
  double new_angle = std::acos((start_point.x - first_point_.x) / getDist(first_point_, second_point_));
  while ((compareDoubles(new_point.x, start_point.x)) || (compareDoubles(new_point.y, start_point.y)))
  {
    new_angle += step_angle;
    start_point_temp.x = first_point_.x + getDist(first_point_, second_point_) * std::cos(new_angle);
    start_point_temp.y = first_point_.y + getDist(first_point_, second_point_) * std::sin(new_angle);
    new_point = start_point_temp;
    bot = std::min(bot, start_point_temp.y);
    top = std::max(top, start_point_temp.y);
    left = std::min(left, start_point_temp.x);
    right = std::max(right, start_point_temp.x);
  }
  return {right - left, top - bot, {(right + left) / 2.0, (top + bot) / 2.0}};
}

void tkach::Regular::move(const double add_to_x, const double add_to_y)
{
  addToPoint(first_point_, add_to_x, add_to_y);
  addToPoint(second_point_, add_to_x, add_to_y);
  addToPoint(third_point_, add_to_x, add_to_y);
}

void tkach::Regular::move(const point_t& point_to_move)
{
  addToPoint(second_point_, point_to_move.x - first_point_.x, point_to_move.y - first_point_.y);
  addToPoint(third_point_, point_to_move.x - first_point_.x, point_to_move.y - first_point_.y);
  first_point_ = point_to_move;
}

void tkach::Regular::doUnsafeScale(const double multiplier)
{
  second_point_ = getShiftedPointFromAnother(second_point_, first_point_, multiplier);
  third_point_ = getShiftedPointFromAnother(third_point_, first_point_, multiplier);
}
