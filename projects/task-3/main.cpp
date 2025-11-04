#include <iostream>
#include <functional>
#include <limits>
#include "hashMap.hpp"
#include "circlesAreaCounter.hpp"

int main()
{
    shapkov::App app;
    shapkov::HashMap< std::string, std::function < void() > > cmds;
    cmds["circle"] = std::bind(shapkov::newCircle, std::ref(std::cin), std::ref(std::cout), std::ref(app.shapes));
    cmds["show"] = std::bind(shapkov::show, std::ref(std::cin), std::ref(std::cout), std::cref(app.shapes));

    std::string command;
    while (!(std::cin >> command).eof())
    {
        try
        {
            cmds.at(command)();
        }
        catch (...)
        {
            if (std::cin.fail())
            {
                std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    return 0;
}