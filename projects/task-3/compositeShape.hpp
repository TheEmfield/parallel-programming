#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "circle.hpp"

namespace shapkov
{
    class CompositeShape
    {
    public:
        CompositeShape(int numberShapes);
        CompositeShape(const CompositeShape &obj);
        CompositeShape(CompositeShape &&rhs) noexcept;
        ~CompositeShape();
        void swap(CompositeShape &rhs) noexcept;
        CompositeShape &operator=(const CompositeShape &obj);
        CompositeShape &operator=(CompositeShape &&obj) noexcept;
        CompositeShape &operator+=(Shape &shape);
        rectangle_t getFrameRectangle() const;
        double getArea() const;
        CompositeShape *clone() const;
        void expanse(size_t new_size);

    private:
        size_t numberShapes_;
        size_t realNumberShapes_ = 0;
        Shape **shapes_{nullptr};
    };
}
#endif
