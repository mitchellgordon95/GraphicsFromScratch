#include "tiffstat_module.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <fstream>
#include "endian_stream_reader.h"

CLI_TiffStat::~CLI_TiffStat()
{
}

void CLI_TiffStat::execute(std::vector<char *> &params)
{
    std::ifstream file(params[0], std::ios::binary);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }

    char endianess[3];
    file.read(endianess, 2);
    endianess[2] = '\0';

    std::cout << "Endianess: " << endianess << std::endl; 
    
    bool littleEndian = (strncmp(endianess, "II", 2) == 0); 
    EndianStreamReader reader(littleEndian);

    uint16_t magicNo = reader.getShort(file); 
    std::cout << "Magic Number: " << magicNo << std::endl;

    uint32_t ifd_address = reader.getInt(file);
    std::cout << "IFD Address: " << ifd_address << std::endl;

    file.seekg(ifd_address, std::ios::beg);
    uint16_t ifd_count = reader.getInt(file); 
    std::cout << "IFD Count: " << ifd_count << std::endl;
}
