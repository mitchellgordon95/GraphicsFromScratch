#include "color_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Color::~CLI_Color()
{
}

void CLI_Color::execute(std::vector<char *> &params)
{
    float args[3];
    for (size_t i = 0; i < params.size(); ++i)
    {
       args[i] = CLI_Module::parseNumericalArg(params[i]);
    }

    std::cout << " R=" << args[0] << " ";
    std::cout << " G=" << args[1] << " ";
    std::cout << " B=" << args[2] << " ";
    
    std::cout << std::endl;
}
