#include "cli_global.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

// Allocate space in the object file for static members.
int CLI_Global::imageWidth;
int CLI_Global::imageHeight;
GLubyte * CLI_Global::imageArray = 0;

// Resizes the image on the screen, clearing the image.
void CLI_Global::resizeImage(int height, int width) {

	// Tear down the old image, if necessary.
	if (imageArray != 0)
		free(imageArray);

	imageWidth = width;
	imageHeight = height;

	// Initialize the new arrays
	imageArray = (GLubyte * ) malloc(width * height * 3 * sizeof(GLubyte));

}

GLubyte * CLI_Global::getPixel(int row, int col) {
	return imageArray + (row * imageWidth + col) * 3;
}

void CLI_Global::setPixel(int row, int col, int R, int G, int B) {

	GLubyte * pixel = getPixel(row, col);
	*pixel = R;
	*(pixel + 1) = G;
	*(pixel + 2) = B;

}
