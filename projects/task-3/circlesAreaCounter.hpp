#ifndef CIRCLES_AREA_COUNTER_HPP
#define CIRCLES_AREA_COUNTER_HPP

#include <string>
#include "hashMap.hpp"
#include "circle.hpp"

namespace shapkov
{
    struct App
    {
        HashMap<std::string, Circle> shapes;
        HashMap< std::string, HashMap < std::string, Circle > > sets;
    };

    void newCircle(std::istream &in, std::ostream &out, HashMap<std::string, Circle> &shapes);
    void show(std::istream &in, std::ostream &out, const HashMap<std::string, Circle> &shapes);
}

#endif