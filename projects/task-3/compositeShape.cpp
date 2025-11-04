#include "compositeShape.hpp"
#include <algorithm>

shapkov::CompositeShape::CompositeShape(int numberShapes):
    numberShapes_(numberShapes)
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
        for (int i = 0; i < numberShapes_; i++)
        {
            if (obj.shapes_[i])
            {
                shapes_[i] = obj.shapes_[i]->clone();
            }
        }
    }
    catch (const std::bad_alloc &)
    {
        for (int i = 0; i < numberShapes_; i++)
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
        for (int i = 0; i < numberShapes_; i++)
        {
            delete shapes_[i];
        }
        delete[] shapes_;
    }
}

shapkov::CompositeShape &shapkov::CompositeShape::operator+=(Shape &shape)
{
    if (realNumberShapes_ >= numberShapes_) {
        expanse(numberShapes_ * 2 + 1);
    }
    shapes_[realNumberShapes_] = shape.clone();
    realNumberShapes_++;
    return *this;
}

rectangle_t shapkov::CompositeShape::getFrameRectangle() const
{
    // double minX = 0,
    // 	minY = 0,
    // 	maxX = 0,
    // 	maxY = 0;
    // point_t leftCoord,
    // 	rightCoord;
    // for (int i = 0; i < numberShapes_; i++) {
    // 	if (shapes_[i]) {
    // 		rectangle_t obj = shapes_[i]->getFrameRectangle();
    // 		leftCoord = point_t(obj.getPos().getX() - (obj.getWidth() / 2), obj.getPos().getY() - (obj.getHeight() / 2));
    // 		rightCoord = point_t(obj.getPos().getX() + (obj.getWidth() / 2), obj.getPos().getY() + (obj.getHeight() / 2));
    // 		if (i == 0) {
    // 			minX = leftCoord.getX();
    // 			minY = leftCoord.getY();
    // 			maxX = rightCoord.getX();
    // 			maxY = rightCoord.getY();
    // 		}
    // 		else {
    // 			minX = std::min(minX, leftCoord.getX());
    // 			minY = std::min(minY, leftCoord.getY());
    // 			maxX = std::max(maxX, rightCoord.getX());
    // 			maxY = std::max(maxY, rightCoord.getY());
    // 		}
    // 	}
    // }
    // return rectangle_t(maxX - minX, maxY - minY, point_t((maxX + minX) / 2, (maxY + minY) / 2));
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
    
}

shapkov::CompositeShape *shapkov::CompositeShape::clone() const
{
    CompositeShape *shape = new CompositeShape(*this);
    return shape;
}

void shapkov::CompositeShape::expanse(size_t new_size)
{
  Shape** new_shapes = new Shape*[new_size];
  for (size_t i = 0; i < numberShapes_; i++)
  {
    new_shapes[i] = shapes_[i];
  }
  delete[] shapes_;
  shapes_ = new_shapes;
  numberShapes_ = new_size;
}