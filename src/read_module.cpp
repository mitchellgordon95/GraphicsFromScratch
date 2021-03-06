#include "read_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Read::~CLI_Read()
{
}

void CLI_Read::execute(std::vector<char *> &params)
{
    ++depth_count;

    if (depth_count > 32)
        throw std::runtime_error("Maximum recursive read depth reached.");

    std::ifstream file(params[0]);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }
    else
    {
        std::cout << "Reading script " << params[0] << std::endl;

        char next_line[1024];

        while (!file.eof())
        {
            file.getline(next_line, 1024);
            
            bool isComment = false;

            for (size_t i = 0 ; i < strlen(next_line); ++i) {
            	if (next_line[i] == '\t' || next_line[i] == ' ')
            		continue;
            	else {
            		isComment = (next_line[i] == '#');
            		break;
            	}
            }

            if (isComment)
                continue;

            Dispatcher::getInstance().interpret( next_line );
        }
        
        std::cout << "End script " << params[0] << std::endl;
    }

    file.close();

    --depth_count;
}
