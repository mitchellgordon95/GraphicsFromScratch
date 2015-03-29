#ifndef CLI_GLOBAL_H
#define CLI_GLOBAL_H

#include <vector>
#include <cstddef>
#include <GL/glut.h>
#include "dispatcher_module.h"

// Global access to things related to drawing.
namespace CLI_Global {

	// Determines whether modules should print diagnostics
	extern bool diagnostics;

	struct Pixel {
		GLubyte R;
		GLubyte G;
		GLubyte B;
	};

	struct Image {
		Pixel * buffer;
		int width;
		int height;
	};

	// The image that will be drawn on the screen
	extern Image displayImage;

	// Resize the image, clearing any pixels that have been set.
	void resizeImage(int width, int height);

	// Clears the image to black
	void clearImage();
	void clearImage(Image image);

	// Allocates a new image in memory.
	Image createImage(int width, int height);

	// Frees the image in memory
	void deleteImage(Image image);

	// Retrieves a pointer to a pixel in the buffer. Defaults to the currently displayed image.
	Pixel * getPixel(int row, int col);

	// Retrieves a pointer to a pixel in the buffer.
	Pixel * getPixel(int row, int col, Image image);

	// Set a pixel to a certain RGB color. Defaults to the currently displayed image.
	void setPixel(int row, int col, Pixel p);

	// Set a pixel to a certain RGB color.
	void setPixel(int row, int col, Pixel p, Image image);

}

#endif
