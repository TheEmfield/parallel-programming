#include "circlesAreaCounter.hpp"
#include <string>
#include <cmath>
#include "circle.hpp"

void shapkov::new_circle(std::istream &in, HashMap<std::string, Circle> &shapes)
{
    std::string name;
    int r;
    double x, y;
    in >> name >> r >> x >> y;
    if (!in || shapes.find(name) != shapes.end())
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
    shapes.insert(name, Circle({x, y}, r));
}

void shapkov::show(std::istream &in, std::ostream &out, const HashMap<std::string, Circle> &shapes)
{
    std::string name;
    in >> name;
    auto crl = shapes.find(name);
    if (crl == shapes.end())
    {
        throw std::logic_error("<INVALID COMMAND>");
    }
    out << crl->second << "\n";
}

void shapkov::new_set(std::istream &in, App &app)
{
    std::string name;
    size_t size;
    in >> name >> size;
    if (!in || app.sets.find(name) != app.sets.end())
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
    HashMap<std::string, Circle> shapes;
    std::string shape;
    for (size_t i = 0; i < size; i++)
    {
        in >> shape;
        auto shape_it = app.shapes.find(shape);
        if (shape_it != app.shapes.end())
        {
            shapes.insert(shape_it->first, shape_it->second);
        }
        else
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
    }
    app.sets.insert(name, std::move(shapes));
}

void shapkov::show_set(std::istream &in, std::ostream &out, const App &app)
{
    std::string name;
    in >> name;
    auto set = app.sets.find(name);
    if (set == app.sets.end())
    {
        throw std::logic_error("<INVALID COMMAND>");
    }
    for (auto it = set->second.cbegin(); it != set->second.cend(); it++)
    {
        out << it->second << "\n";
    }
}

void shapkov::frame_rect(std::istream &in, std::ostream &out, const HashMap<std::string, Circle> &shapes)
{
    std::string name;
    in >> name;
    auto crl = shapes.find(name);
    if (crl == shapes.end())
    {
        throw std::logic_error("<INVALID COMMAND>");
    }
    rectangle_t rect = crl->second.getFrameRect();
    out << "(" << rect.pos.x - rect.width / 2 << " " << rect.pos.y - rect.height / 2 << ") (" << rect.pos.x + rect.width / 2 << " " << rect.pos.y + rect.height / 2 << ")\n";
}

void shapkov::frame_set(std::istream &in, std::ostream &out, const App &app)
{
    std::string name;
    in >> name;
    auto set = app.sets.find(name);
    if (set == app.sets.end())
    {
        throw std::logic_error("<INVALID COMMAND>");
    }
    const auto& shapes = set->second;
    auto it = shapes.cbegin();
    rectangle_t rect = it->second.getFrameRect();
    double min_x = rect.pos.x - rect.width / 2;
    double max_x = rect.pos.x + rect.width / 2;
    double min_y = rect.pos.y - rect.height / 2;
    double max_y = rect.pos.y + rect.height / 2;
    ++it;
    for (; it != shapes.cend(); ++it)
    {
        rectangle_t r = it->second.getFrameRect();
        min_x = std::fmin(min_x, r.pos.x - r.width / 2);
        min_y = std::fmin(min_y, r.pos.y - r.height / 2);
        max_x = std::fmax(max_x, r.pos.x + r.width / 2);
        max_y = std::fmax(max_y, r.pos.y + r.height / 2);
    }
    out << "(" << min_x << " " << min_y << ") (" << max_x << " " << max_y << ")\n";
}