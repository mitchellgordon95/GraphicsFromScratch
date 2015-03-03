#include "cli_global.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace CLI_Global;

// Allocate space in the object file for static members.
int CLI_Global::imageWidth;
int CLI_Global::imageHeight;
Pixel * CLI_Global::imageArray = 0;

// Resizes the image on the screen, clearing the image.
void CLI_Global::resizeImage(int width, int height) {

	// Tear down the old image, if necessary.
	if (imageArray != 0)
		free(imageArray);

	imageWidth = width;
	imageHeight = height;

	// Initialize the new arrays
	imageArray = (Pixel * ) malloc(width * height * sizeof(Pixel));

	// Reequest that the window be resized to the image shape.
	glutReshapeWindow(width, height);
}

Pixel * CLI_Global::getPixel(int row, int col) {
	if (row > (int) imageHeight || col > (int) imageWidth)
		throw std::runtime_error("Invalid pixel coordinates.");

	return imageArray + (row * imageWidth + col);
}

void CLI_Global::setPixel(int row, int col, Pixel p) {

	Pixel * pixel = getPixel(row, col);
	pixel->R = p.R;
	pixel->G = p.G;
	pixel->B = p.B;

}
