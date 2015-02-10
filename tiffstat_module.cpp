#include "tiffstat_module.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
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

    parseTiffMeta(file, true);    
}

std::map<uint16_t, IFD_Entry> CLI_TiffStat::parseTiffMeta(std::ifstream &file, bool verbose) {
    char endianess[3];
    file.read(endianess, 2);
    endianess[2] = '\0';

    
    bool littleEndian = (strncmp(endianess, "II", 2) == 0); 
    EndianStreamReader reader(littleEndian);

    uint16_t magicNo = reader.getShort(file); 

    uint32_t ifd_address = reader.getInt(file);

    file.seekg(ifd_address, std::ios::beg);
    uint16_t ifd_count = reader.getInt(file); 

    if(verbose) {
        std::cout << "Endianess: " << endianess << std::endl; 
        std::cout << "Magic Number: " << magicNo << std::endl;
        std::cout << "IFD Address: " << ifd_address << std::endl;
        std::cout << "IFD Count: " << ifd_count << std::endl;
    }    

    std::map<uint16_t, IFD_Entry> entries;

    for (int i = 0 ; i < ifd_count; ++i) {
        IFD_Entry entry;
        entry.tag = reader.getShort(file);
        entry.type = reader.getShort(file);
        entry.count = reader.getInt(file);
        entry.value = reader.getInt(file);

        
    }    

    return entries;
}

