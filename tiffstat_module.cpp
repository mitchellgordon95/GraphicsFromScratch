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

    uint16_t magicNo;
    reader.readShort(file, (char *) &magicNo, 1); 

    if (magicNo != 42 || ! (littleEndian || strncmp(endianess, "MM", 2) == 0)) {
        throw std::runtime_error("Unrecognized file type");
    }

    uint32_t ifd_address;
    reader.readInt(file, (char *) &ifd_address, 1);

    file.seekg(ifd_address, std::ios::beg);
    uint16_t ifd_count;
    reader.readShort(file, (char * ) &ifd_count, 1); 

    if(verbose) {
        std::cout << "Endianess: " << endianess << std::endl; 
        std::cout << "Magic Number: " << magicNo << std::endl;
        std::cout << "IFD Address: " << ifd_address << std::endl;
        std::cout << "IFD Count: " << ifd_count << std::endl;
    }    

    std::map<uint16_t, IFD_Entry> entries;

    for (int i = 0 ; i < ifd_count; ++i) {
        IFD_Entry entry = IFD_Entry::readFromFile(file, reader); 

        entries.insert(std::pair<uint16_t, IFD_Entry>(entry.tag, entry));

        if (verbose) {
            std::cout << Tiff_Tag_Names.at(entry.tag) << " (" << entry.tag << ") ";
            std::cout << Tiff_Type_Names.at(entry.type) << " (" << entry.type << ") ";
            std::cout << entry.count << "<";

            entry.printValues(20);

            std::cout << std::endl;
        } 
        
        if (file.fail())
            throw std::runtime_error("Error parsing TIFF metadata");
    }    

    return entries;
}

