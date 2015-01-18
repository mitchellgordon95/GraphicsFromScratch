#include "color_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>

CLI_Color::~CLI_Color()
{
}

bool CLI_Color::execute(std::vector<char *> &params)
{
    for (std::size_t i = 0; i < params.size(); ++i)
        std::cout << params[i] << " ";
    
    std::cout << std::endl;
    return true;
}
