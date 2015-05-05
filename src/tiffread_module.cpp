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
#include "cli_global.h"

// Initialize the static map for the last metadata read
std::map<uint16_t, IFD_Entry> CLI_Tiffread::lastRead;

CLI_Tiffread::~CLI_Tiffread()
{
}

void CLI_Tiffread::execute(std::vector<char *> &params)
{
    std::ifstream file(params[0], std::ios::binary);
    
    if ( !file.is_open() )
    {
        throw std::invalid_argument(std::string("Could not read file ") + params[0]);
    }

    std::map<uint16_t, IFD_Entry> entries = CLI_Tiffstat::parseTiffMeta(file, false);

    // We don't support compression yet
    if (entries[259].getValue<uint16_t>(0) != 1)
    	throw std::runtime_error("We don't support compressed TIFFs yet.");

    // Get the image width and length
    uint32_t imageWidth = entries[256].getValue<uint32_t>(0);
    uint32_t imageHeight = entries[257].getValue<uint32_t>(0);

    // Resize the image if necessary.
    if ((int) imageWidth != CLI_Global::displayImage.width || (int) imageHeight != CLI_Global::displayImage.height)
    	CLI_Global::resizeImage(imageWidth, imageHeight);


    TiffColorScheme scheme = getColorScheme(entries);

    IFD_Entry offsetEntry = entries[273];
    IFD_Entry byteCountsEntry = entries[279];

    if (offsetEntry.count != byteCountsEntry.count)
    	throw std::runtime_error("(Malformed Tiff) Number of strip offsets and byte counts don't match.");

    uint32_t rowsPerStrip = entries[278].getValue<uint32_t>(0);

    uint64_t currentRow = 0;

    // Read all the strips into memory.

    unsigned char * buffer = 0;
    if (scheme == GrayScale8bit)
    	buffer = new unsigned char[imageWidth];
    else
    	// 24bitRGB
    	buffer = new unsigned char[imageWidth * 3];

	int photometric = entries[262].getValue<uint16_t>(0);

    for (size_t i = 0 ; i < offsetEntry.count; ++i) {
    	// Seek to the beginning of the strip
    	file.seekg(offsetEntry.getValue<uint32_t>(i), std::ios::beg);

    	// Read the rows from the strip into memory
    	for (size_t stripRow = 0; stripRow < rowsPerStrip && currentRow < imageHeight; ++stripRow) {
    		// If it's already in 24 bit RGB, then we don't have to do any converting.
    		if (scheme == RGB24bit) {
    			file.read((char*) buffer, imageWidth * 3);
    			for (size_t i = 0; i < imageWidth; ++i) {
    				int bufferPos = i * 3;
    				// We have to flip the image, because TIFF is top to bottom, but OpenGL is bottom to top
    				CLI_Global::setPixel(imageHeight - currentRow - 1, i, { (GLfloat)buffer[bufferPos] / 255,
    						(GLfloat)buffer[bufferPos + 1] / 255, (GLfloat)buffer[bufferPos+2] / 255});
    			}
    		}
    		else if (scheme == GrayScale8bit) {
    			// Since we're rendering in 24bit RGB, we'll have to spread the grayscale
    			// values out.
    			file.read((char *)buffer, imageWidth);
    			for (size_t col = 0; col < imageWidth; ++col) {
    				GLfloat val = (GLfloat) buffer[col];
    				// Normalize to 0 to 1 range
    				val = val / 255;

					// If 0 is white we have to flip the values.
					if (photometric == 0)
						val = 1 - val;

					CLI_Global::setPixel(imageHeight - currentRow - 1, col, {val, val, val});
    			}
    		}
    		++currentRow;
    	}
    }

    // Clean up
    delete [] buffer;
    file.close();

    // Store the entries in case TiffWrite wants it later
    CLI_Tiffread::lastRead = std::map<uint16_t, IFD_Entry>(entries);

    // Make the window refresh.
    glutPostRedisplay();

    std::cout << "Displaying TIFF file " << params[0] << " on screen." << std::endl;
}

TiffColorScheme CLI_Tiffread::getColorScheme (std::map<uint16_t, IFD_Entry> &entries) {

	int photometric = entries[262].getValue<uint16_t>(0);

    // We don't support palette color images
    if (photometric == 3)
    	throw std::runtime_error("We don't support palette color images yet.");

	IFD_Entry bps = entries[258];
	if ( bps.count == 1 && bps.getValue<uint16_t>(0) == 8 )
		return GrayScale8bit;
	else if (bps.count == 3 && bps.getValue<uint16_t>(0) == 8
							&& bps.getValue<uint16_t>(1) == 8
							&& bps.getValue<uint16_t>(2) == 8
							&& photometric == 2)
		return RGB24bit;
	else
		throw std::runtime_error("Unsupported color scheme.");

}

