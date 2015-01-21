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
    char * endptr;
    float args[3];
    for (size_t i = 0; i < params.size(); ++i)
    {
        args[i] = strtod(params[i], &endptr);
        
        // If endptr doesn't point to the end of the string
        // then there was part of the token we couldn't parse.
        if (*endptr != '\0')
        {
            char msg[1024];
            sprintf(msg, "Could not parse arg %d", (int) i);
            throw std::invalid_argument(msg);
        }
    }
    std::cout << " X=" << args[0] << " ";
    std::cout << " Y=" << args[1] << " ";
    std::cout << " Z=" << args[2] << " ";

    std::cout << std::endl;
}
