#include "tiffwrite_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <fstream>
#include "tiff_utils.h"
#include "tiffread_module.h"

CLI_TiffWrite::~CLI_TiffWrite()
{
}

void CLI_TiffWrite::execute(std::vector<char *> &params)
{
    std::ofstream file(params[0]);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not open file for writing: ") + params[0]);
    }

    std::map<uint16_t, IFD_Entry> entries = CLI_TiffRead::getLastRead();

}
