#include "tiffread_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <map>
#include <vector>
#include <GL/glut.h>
#include "tiffstat_module.h"

// Get the global image array
// TODO - Make this better
extern GLubyte imageArray[1024][1024][3];

CLI_TiffRead::~CLI_TiffRead()
{
}

void CLI_TiffRead::execute(std::vector<char *> &params)
{
    std::ifstream file(params[0]);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }

    std::map<uint16_t, IFD_Entry> entries = CLI_TiffStat::parseTiffMeta(file, false);

    // We don't support compression yet
    if (entries[259].getValue<uint16_t>(0) != 1)
    	throw std::runtime_error("We don't support compressed TIFFs yet.");

    // Get the image width and length
    uint32_t imageWidth = entries[256].getValue<uint32_t>(0);
    uint32_t imageHeight = entries[257].getValue<uint32_t>(0);

    // We don't support images greater than 1024 x 1024 yet
    if (imageWidth > 1024 || imageHeight > 1024)
    	throw std::runtime_error("We don't support images bigger than 1024x1024 yet.");

    // We only support 8-bit grayscale and 24-bit RGB
    enum ColorScheme { RGB24bit, GrayScale8bit};
    ColorScheme scheme;

    IFD_Entry bps = entries[258]; // Bits per sample
    if ( bps.count == 1 && bps.getValue<uint16_t>(0) == 8 )
    	scheme = GrayScale8bit;
    else if (bps.count == 3 && bps.getValue<uint16_t>(0) == 8
    						&& bps.getValue<uint16_t>(1) == 8
    						&& bps.getValue<uint16_t>(2) == 8)
    	scheme = RGB24bit;
    else
    	throw std::runtime_error("Unsupported color scheme.");

    IFD_Entry offsetEntry = entries[273];
    IFD_Entry byteCountsEntry = entries[279];

    if (offsetEntry.count != byteCountsEntry.count)
    	throw std::runtime_error("(Malformed Tiff) Number of strip offsets and byte counts don't match.");

    uint32_t rowsPerStrip = entries[278].getValue<uint32_t>(0);

    long currentRow = 0;

    // Read all the strips into memory.

    char * buffer = 0;
    if (scheme == GrayScale8bit)
    	buffer = new char[imageWidth];

    for (size_t i = 0 ; i < offsetEntry.count; ++i) {
    	// Seek to the beginning of the strip
    	file.seekg(offsetEntry.getValue<uint32_t>(i), std::ios::beg);

    	// Read the rows from the strip into memory
    	for (size_t stripRow = 0; stripRow < rowsPerStrip && currentRow < imageHeight; ++stripRow) {
    		// If it's already in 24 bit RGB, then we don't have to do any converting.
    		if (scheme == RGB24bit) {
    			// We have to flip the image, because TIFF is top to bottom, but OpenGL is bottom to top.
    			file.read((char*) imageArray[imageHeight - currentRow][0], imageWidth * 3);
    		}
    		else if (scheme == GrayScale8bit) {
    			// Since we're rendering in 24bit RGB, we'll have to spread the grayscale
    			// values out.
    			file.read(buffer, imageWidth);
    			for (size_t col = 0; col < imageWidth; ++col) {
    				imageArray[imageHeight - currentRow][col][0] = buffer[col];
    				imageArray[imageHeight - currentRow][col][1] = buffer[col];
    				imageArray[imageHeight - currentRow][col][2] = buffer[col];
    			}
    		}
    		++currentRow;
    	}
    }

    // Clean up
    delete [] buffer;

    // Make the window refresh.
    glutPostRedisplay();

    std::cout << "read file " << params[0] << std::endl;
}
