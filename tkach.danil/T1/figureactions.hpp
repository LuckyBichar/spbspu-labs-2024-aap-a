#ifndef FIGUREACTIONS_HPP
#define FIGUREACTIONS_HPP

#include <cstddef>
#include <iostream>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace tkach
{
  void doSafeIsoScaleCompShape(CompositeShape& shape_array, double scale_coef, const point_t& scale_point);
  void doUnsafeIsoScaleCompShape(CompositeShape& shape_array, double scale_coef, const point_t& scale_point);
}

#endif
