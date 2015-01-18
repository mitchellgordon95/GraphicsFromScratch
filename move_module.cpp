#include "move_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>

CLI_Move::~CLI_Move()
{
}

bool CLI_Move::execute(std::vector<char *> &params)
{
    for (std::size_t i = 0; i < params.size(); ++i)
        std::cout << params[i] << " ";
    
    std::cout << std::endl;
    return true;
}
