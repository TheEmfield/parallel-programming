#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
namespace shapkov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual rectangle_t getFrameRect() const = 0;
    virtual Shape* clone() const = 0;
  };
}
#endif