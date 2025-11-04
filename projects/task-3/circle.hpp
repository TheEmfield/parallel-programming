#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
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
        friend std::ostream& operator<<(std::ostream& out, const Circle& circle);

    private:
        point_t center_;
        int radius_;
    };

    std::ostream& operator<<(std::ostream& out, const Circle& circle);
}

#endif