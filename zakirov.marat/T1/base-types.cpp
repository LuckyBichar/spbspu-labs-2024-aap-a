#include "base-types.hpp"
#include <cmath>

double zakirov::get_distance_x(zakirov::point_t first_p, zakirov::point_t second_p)
{
  double big_num = first_p.x > second_p.x ? first_p.x : second_p.x;
  double small_num = first_p.x < second_p.x ? first_p.x : second_p.x;
  return big_num - small_num;
}

double zakirov::get_distance_y(zakirov::point_t first_p, zakirov::point_t second_p)
{
  double big_num = first_p.y > second_p.y ? first_p.y : second_p.y;
  double small_num = first_p.y < second_p.y ? first_p.y : second_p.y;
  return big_num - small_num;
}

double get_distance(zakirov::point_t first_p, zakirov::point_t second_p)
{
  double squared_x = pow(zakirov::get_distance_x(first_p, second_p), 2);
  double squared_y = pow(zakirov::get_distance_y(first_p, second_p), 2);
  return sqrt(squared_x + squared_y);
}
