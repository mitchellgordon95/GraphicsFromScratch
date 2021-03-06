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

CLI_Tiffstat::~CLI_Tiffstat()
{
}

void CLI_Tiffstat::execute(std::vector<char *> &params)
{
    std::ifstream file(params[0], std::ios::binary);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }

    std::cout << "Metadata for " << params[0] << ":" << std::endl;

    std::cout << std::endl;
    parseTiffMeta(file, true);    
}

std::map<uint16_t, IFD_Entry> CLI_Tiffstat::parseTiffMeta(std::ifstream &file, bool verbose) {

    char endianess[3];
    file.read(endianess, 2);
    endianess[2] = '\0';

    bool littleEndian = (strncmp(endianess, "II", 2) == 0); 
    EndianStreamReader reader(littleEndian);

    uint16_t magicNo;
    reader.readShort(file, (char *) &magicNo, 1); 

    if (magicNo != 42)
        throw std::runtime_error("Unrecognized file type, bad magic number.");
    else if (!littleEndian && strncmp(endianess, "MM", 2) != 0)
    	throw std::runtime_error("Unrecognized file type, endianess not specified.");

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
			// Print the tag name and number
        	if (Tiff_Tag_Names.find(entry.tag) != Tiff_Tag_Names.end())
				std::cout << Tiff_Tag_Names.at(entry.tag);
			else
				std::cout << "*Unknown*";
			std::cout << " (" << entry.tag << ") ";

			// Print the tag type and type number
			if (Tiff_Type_Names.find(entry.type) != Tiff_Type_Names.end())
				std::cout << Tiff_Type_Names.at(entry.type);
			else
				std::cout << "*Unknown*";
			std::cout << " (" << entry.type << ") ";

			std::cout << entry.count << "<";

			entry.printValues(20);

			std::cout << std::endl;

        } 
        
        if (file.fail())
            throw std::runtime_error("Error parsing TIFF metadata");
    }    

    return entries;
}

