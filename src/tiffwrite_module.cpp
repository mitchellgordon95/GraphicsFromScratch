#include "tiffwrite_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <GL/glut.h>
#include "tiff_utils.h"
#include "tiffread_module.h"
#include "cli_global.h"

CLI_Tiffwrite::~CLI_Tiffwrite()
{
}

void CLI_Tiffwrite::execute(std::vector<char *> &params)
{
    std::ofstream file(params[0], std::ios::binary);
    
    if ( !file.is_open() )
        throw std::invalid_argument(std::string("Could not open file for writing: ") + params[0]);


    std::map<uint16_t, IFD_Entry> entries = CLI_Tiffread::getLastRead();

    if (entries.empty())
    	throw std::runtime_error("TiffRead has not been called yet.");

    // Write all the basic meta stuff

    // First find the endianess of the machine
    short int one = 1;
	char *byte = (char *) &one;
	int machineLittleEndian = byte[0];

    if (machineLittleEndian == 1)
    	file.write("II", 2);
    else
    	file.write("MM", 2);

    uint16_t magicNo = 42;
    file.write((char *) &magicNo, 2);

    //And the offset of the first IFD (which will be immediately after this header
    uint32_t IFD_Offset = 8;
    file.write((char*) &IFD_Offset, 4);

    uint16_t IFD_Count = entries.size();
    file.write((char*) &IFD_Count, 2);

    // Skip writing the IFD Entries for now.
    size_t entries_byte_size = IFD_Count * 12;
    file.seekp(entries_byte_size, std::ios::cur);

    // Write the image data out into the file.

    TiffColorScheme scheme = CLI_Tiffread::getColorScheme(entries);

    int x0 = (int) parseNumericalArg(params[1]);
    int y0 = (int) parseNumericalArg(params[2]);
    int x1 = (int) parseNumericalArg(params[3]);
    int y1 = (int) parseNumericalArg(params[4]);

    uint32_t newWidth = x1 - x0;
    uint32_t newLength = y1 - y0;

    uint32_t rowByteSize;
    if (scheme == GrayScale8bit)
    	rowByteSize = newWidth * 1;
    else
    	rowByteSize = newWidth * 3;

    uint32_t imageByteSize = rowByteSize * newLength;

    // Write out the image data
	for (size_t i = 0; i < newLength; ++i) {
		// If it's already in 24 bit RGB, then we don't have to do any color converting.
		if (scheme == RGB24bit) {
			// We have to flip the image, because TIFF is top to bottom, but OpenGL is bottom to top.
			file.write((char*) CLI_Global::getPixel(y1 - i, 0), rowByteSize);
		}
		else if (scheme == GrayScale8bit) {
			// Since we're rendering in 24bit RGB, we'll have to take a single value
			// from each pixel.
			for (size_t k = 0; k < newWidth; ++k)
				file.write((char*)CLI_Global::getPixel(y1 - i, k), 1);
		}
	}

	// Make the tags right.

    // Set the new width and and length
    entries[256].setValue(&newWidth, 4, 1, LONG);
    entries[257].setValue(&newLength, 4, 1, LONG);

    // Reset the photometric interpretation, if necessary
    if (scheme == GrayScale8bit) {
    	uint16_t x = 1;
    	entries[262].setValue(&x, 2, 1, SHORT);
    }

    // We're only going to use one strip
    uint32_t dataOffset = 10 + entries_byte_size;
    entries[273].setValue(&dataOffset, 4, 1, LONG);
    entries[278].setValue(&newLength, 4, 1, LONG); // RowsPerStrip
    entries[279].setValue(&imageByteSize, 4, 1, LONG); // StripByteCounts

    // The values from the IFD will go after the image data
    uint32_t valuePointer = file.tellp();

    file.seekp(IFD_Offset + 2, std::ios::beg);

    // Write out all the IFD entries
    for (std::map<uint16_t, IFD_Entry>::iterator i = entries.begin();
    		i != entries.end(); ++i )
    	valuePointer = i->second.writeToFile(file, valuePointer);

    // Close the files
    file.close();

    std::cout << "Wrote TIFF to: " << params[0] << std::endl;
}

