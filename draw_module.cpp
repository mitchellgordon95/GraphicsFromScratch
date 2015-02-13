#include "draw_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Draw::~CLI_Draw()
{
}

void CLI_Draw::execute(std::vector<char *> &params)
{
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
