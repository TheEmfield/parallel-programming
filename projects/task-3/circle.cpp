#include "circle.hpp"

shapkov::Circle::Circle(const point_t &center, int radius): center_(center), radius_(radius) {}
shapkov::Circle::~Circle() {}
shapkov::Shape* shapkov::Circle::clone() const {
    return new Circle(*this);
}
double shapkov::Circle::getAreaMonteCarlo() const
{
    const int tries = 1'000'000;
    std::mt19937 coordGenerator(20);
    std::uniform_real_distribution<double> dist(0, radius_);
    size_t cntGood = 0;
    for (size_t i = 0; i < tries; i++)
    {
        double coordX = dist(coordGenerator), coordY = dist(coordGenerator);
        if ((coordX * coordX + coordY * coordY) <= radius_ * radius_)
        {
            cntGood++;
        }
    }
    return static_cast<double>(cntGood) / (tries) * 4 * radius_ * radius_;
}
rectangle_t shapkov::Circle::getFrameRect() const
{
    return rectangle_t{2.0 * radius_, radius_ * 2.0, center_};
}
