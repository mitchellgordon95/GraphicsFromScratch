#include "read_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Read::~CLI_Read()
{
}

bool CLI_Read::execute(std::vector<char *> &params)
{
    ++depth_count;

    if (depth_count > 32)
        throw std::runtime_error("Maximum recursive read depth reached.");

    std::ifstream file(params[0]);
    
    if ( !file.is_open() )
    {
        std::cout << "Error: could not read " << params[0] << std::endl;
    }
    else
    {
        char next_line[1024];

        while (!file.eof())
        {
            file.getline(next_line, 1024);
            
            // TODO - Trim whitespace for less strict commenting rules
            if ( next_line[0] == '#' )
                continue;

            dispatcher.interpret( next_line );
        }
    }

    --depth_count;
    return true;
}
