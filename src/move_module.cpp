#include "move_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Move::~CLI_Move()
{
}

void CLI_Move::execute(std::vector<char *> &params)
{

	std::cout << "Move: ";
    float args[3];
    for (size_t i = 0; i < params.size(); ++i)
    {
        args[i] = CLI_Module::parseNumericalArg(params[i]);
    }
    std::cout << " X=" << args[0] << " ";
    std::cout << " Y=" << args[1] << " ";
    std::cout << " Z=" << args[2] << " ";
    
    std::cout << std::endl;

}
