#include "circlesAreaCounter.hpp"
#include <string>
#include "circle.hpp"

void shapkov::newCircle(std::istream& in, std::ostream& out, HashMap< std::string, Circle>& shapes)
{
    std::string name;
    int r;
    double x, y;
    in >> name >> r >> x >> y;
    if (std::cin.fail() || shapes.find(name) != shapes.end())
    {
        out << "<INVALID COMMAND>\n";
    }
    shapes.insert(name, Circle({x, y}, r));
}

void shapkov::show(std::istream& in, std::ostream& out, const HashMap< std::string, Circle>& shapes)
{
    std::string name;
    in >> name;
    auto crl = shapes.find(name);
    if (crl == shapes.end())
    {
        out << "<INVALID COMMAND>\n";
    }
    out << crl->second << "\n";
}