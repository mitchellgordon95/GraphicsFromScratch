#include "read_module.h"
#include <string.h>
#include <iostream>
#include <cstddef>
#include <exception>

CLI_Read::~CLI_Read()
{
}

bool CLI_Read::execute(std::vector<char *> &params)
{
    ++call_depth;
    
    if (call_depth > 32)
        throw std::exception("Maximum recursive read depth reached.");

    // Open the file
    
    // Dispatch each line

    

    --call_depth;
    return true;
}
