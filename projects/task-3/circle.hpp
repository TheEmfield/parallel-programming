#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <random>
#include "base-types.hpp"
#include "shape.hpp"

namespace shapkov
{
    class Circle: public Shape
    {
    public:
        Circle(const point_t& center, int radius);
        ~Circle();
        Shape* clone() const;
        double getAreaMonteCarlo() const;
        rectangle_t getFrameRect() const;

    private:
        point_t center_;
        int radius_;
    };
}

#endif