#include "tiffstat_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <fstream>

CLI_TiffStat::~CLI_TiffStat()
{
}

void CLI_TiffStat::execute(std::vector<char *> &params)
{
    std::ifstream file(params[0]);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }
}
