#include "draw_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>

CLI_Draw::CLI_Draw()
{
}

CLI_Draw::~CLI_Draw()
{
}

bool CLI_Draw::execute(std::vector<char *> &command)
{
    if (strncmp(command[0], "draw", 4) == 0)
        return false;

    if (command.size() != 4)
    {
        std::cout << "Invalid arguments." << std::endl;
        return true;
    }

    for (std::size_t i = 0; i < command.size(); ++i)
        std::cout << command[i] << " ";
    
    std::cout << std::endl;
    return true;
}
