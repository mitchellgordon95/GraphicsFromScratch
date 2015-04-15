#include "cli_global.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace CLI_Global;

// Determines whether modules should print diagnostics
bool CLI_Global::diagnostics = false;

// Allocate space in the object file for static members.
Image CLI_Global::displayImage;


inline Pixel operator*(Pixel left, Pixel right) {
	Pixel out;
	out.R = left.R * right.R;
	out.G = left.G * right.G;
	out.B = left.B * right.B;
	return out;
}
inline Pixel operator/(Pixel left, Pixel right) {
	Pixel out;
	out.R = left.R / right.R;
	out.G = left.G / right.G;
	out.B = left.B / right.B;
	return out;
}
inline bool isZero(Pixel p) {
	return (p.R == 0 && p.G == 0 && p.B == 0);
}

// Resizes the image on the screen, clearing the image.
void CLI_Global::resizeImage(int width, int height) {

	// Tear down the old image, if necessary.
	if (displayImage.buffer != 0)
		free(displayImage.buffer);

	displayImage.width = width;
	displayImage.height = height;

	// Initialize the new arrays
	displayImage.buffer = (Pixel * ) malloc(width * height * sizeof(Pixel));

	// Reequest that the window be resized to the image shape.
	glutReshapeWindow(width, height);
}

// Clears the image to black
void CLI_Global::clearImage(Image img) {
	Pixel black;
	black.R = 0;
	black.G = 0;
	black.B = 0;
	for (int i = 0; i < img.height; ++i)
		for (int j = 0; j < img.width; ++j)
			setPixel(i, j, black, img);
}

void CLI_Global::clearImage() {
	clearImage(displayImage);
}

// Allocates an image and its buffer.
Image CLI_Global::createImage(int width, int height) {
	Image out;
	out.width = width;
	out.height = height;
	out.buffer = (Pixel *) malloc(width * height * sizeof(Pixel));

	return out;
}

// Frees an image's buffer in memory
void CLI_Global::deleteImage(Image image) {
	free(image.buffer);
}

Pixel * CLI_Global::getPixel(int row, int col) {
	return getPixel(row, col, displayImage);
}

Pixel * CLI_Global::getPixel(int row, int col, Image image) {
	if (row >= image.height || col >= image.width)
		throw std::runtime_error("Invalid pixel coordinates.");

	return image.buffer + (row * image.width + col);
}

void CLI_Global::setPixel(int row, int col, Pixel p) {
	setPixel(row, col, p, displayImage);
}

void CLI_Global::setPixel(int row, int col, Pixel p, Image image) {

	Pixel * pixel = getPixel(row, col, image);
	pixel->R = p.R;
	pixel->G = p.G;
	pixel->B = p.B;

}
