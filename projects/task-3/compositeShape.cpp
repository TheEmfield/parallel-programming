#include "compositeShape.hpp"
#include <cmath>

shapkov::CompositeShape::CompositeShape(int numberShapes) : numberShapes_(numberShapes)
{
    shapes_ = new Shape *[numberShapes_]{nullptr};
}
shapkov::CompositeShape::CompositeShape(const CompositeShape &obj):
    numberShapes_(obj.numberShapes_),
    realNumberShapes_(obj.realNumberShapes_)
{
    shapes_ = new Shape *[obj.numberShapes_]{nullptr};
    try
    {
        for (size_t i = 0; i < numberShapes_; i++)
        {
            if (obj.shapes_[i])
            {
                shapes_[i] = obj.shapes_[i]->clone();
            }
        }
    }
    catch (const std::bad_alloc &)
    {
        for (size_t i = 0; i < numberShapes_; i++)
        {
            delete shapes_[i];
        }
        delete[] shapes_;
        throw;
    }
}

shapkov::CompositeShape::CompositeShape(CompositeShape &&rhs) noexcept:
    numberShapes_(rhs.numberShapes_),
    realNumberShapes_(rhs.realNumberShapes_),
    shapes_(rhs.shapes_)
{
    rhs.shapes_ = nullptr;
    rhs.realNumberShapes_ = 0;
    rhs.numberShapes_ = 0;
}

shapkov::CompositeShape::~CompositeShape()
{
    if (shapes_)
    {
        for (size_t i = 0; i < numberShapes_; i++)
        {
            delete shapes_[i];
        }
        delete[] shapes_;
    }
}

shapkov::CompositeShape &shapkov::CompositeShape::operator+=(Shape &shape)
{
    if (realNumberShapes_ >= numberShapes_)
    {
        expanse(numberShapes_ * 2 + 1);
    }
    shapes_[realNumberShapes_] = shape.clone();
    realNumberShapes_++;
    return *this;
}

rectangle_t shapkov::CompositeShape::getFrameRectangle() const
{
    double min_x = shapes_[0]->getFrameRect().pos.x - shapes_[0]->getFrameRect().width / 2;
    double max_x = shapes_[0]->getFrameRect().pos.x + shapes_[0]->getFrameRect().width / 2;
    double min_y = shapes_[0]->getFrameRect().pos.y - shapes_[0]->getFrameRect().height / 2;
    double max_y = shapes_[0]->getFrameRect().pos.y + shapes_[0]->getFrameRect().height / 2;
    for (size_t i = 1; i < realNumberShapes_; i++)
    {
        rectangle_t rectangl = shapes_[i]->getFrameRect();
        min_x = std::fmin(min_x, rectangl.pos.x - (rectangl.width / 2));
        min_y = std::fmin(min_y, rectangl.pos.y - (rectangl.height / 2));
        max_x = std::fmax(max_x, rectangl.pos.x + (rectangl.width / 2));
        max_y = std::fmax(max_y, rectangl.pos.y + (rectangl.height / 2));
    }
    double width = max_x - min_x;
    double height = max_y - min_y;
    point_t pos{min_x + (width / 2), min_y + (height / 2)};
    rectangle_t rect{width, height, pos};
    return rect;
}

void shapkov::CompositeShape::swap(CompositeShape &rhs) noexcept
{
    std::swap(numberShapes_, rhs.numberShapes_);
    std::swap(realNumberShapes_, rhs.realNumberShapes_);
    std::swap(shapes_, rhs.shapes_);
}

shapkov::CompositeShape &shapkov::CompositeShape::operator=(const CompositeShape &obj)
{
    if (this == &obj)
    {
        return *this;
    }
    CompositeShape temp(obj);
    swap(temp);
    return *this;
}

shapkov::CompositeShape &shapkov::CompositeShape::operator=(CompositeShape &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }
    swap(obj);
    return *this;
}

double shapkov::CompositeShape::getArea() const
{
    //TODO, BUT I HAVE ALREADY UNDERSTOOD THAT I NEEDNT THIS
    return 1.2;
}

shapkov::CompositeShape *shapkov::CompositeShape::clone() const
{
    CompositeShape *shape = new CompositeShape(*this);
    return shape;
}

void shapkov::CompositeShape::expanse(size_t new_size)
{
    Shape **new_shapes = new Shape *[new_size];
    for (size_t i = 0; i < numberShapes_; i++)
    {
        new_shapes[i] = shapes_[i];
    }
    delete[] shapes_;
    shapes_ = new_shapes;
    numberShapes_ = new_size;
}