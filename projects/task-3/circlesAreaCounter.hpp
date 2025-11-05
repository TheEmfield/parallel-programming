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

    void new_circle(std::istream &in, HashMap<std::string, Circle> &shapes);
    void show(std::istream &in, std::ostream &out, const HashMap<std::string, Circle> &shapes);
    void new_set(std::istream &in, App &app);
    void show_set(std::istream &in, std::ostream &out, const App &app);
    void frame_rect(std::istream &in, std::ostream &out, const HashMap<std::string, Circle> &shapes);
    void frame_set(std::istream &in, std::ostream &out, const App &app);
}

#endif