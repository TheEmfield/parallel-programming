#include <iostream>
#include <functional>
#include <limits>
#include "hashMap.hpp"
#include "circlesAreaCounter.hpp"

int main()
{
    shapkov::App app;
    shapkov::HashMap< std::string, std::function < void() > > cmds;
    cmds["circle"] = std::bind(shapkov::new_circle, std::ref(std::cin), std::ref(app.shapes));
    cmds["show"] = std::bind(shapkov::show, std::ref(std::cin), std::ref(std::cout), std::cref(app.shapes));
    cmds["set"] = std::bind(shapkov::new_set, std::ref(std::cin), std::ref(app));
    cmds["showset"] = std::bind(shapkov::show_set, std::ref(std::cin), std::ref(std::cout), std::cref(app));
    cmds["frame"] = std::bind(shapkov::frame_rect, std::ref(std::cin), std::ref(std::cout), std::cref(app.shapes));
    cmds["frameset"] = std::bind(shapkov::frame_set, std::ref(std::cin), std::ref(std::cout), std::cref(app));

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