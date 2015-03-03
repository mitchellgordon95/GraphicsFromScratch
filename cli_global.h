#ifndef CLI_GLOBAL_H
#define CLI_GLOBAL_H

#include <vector>
#include <cstddef>
#include <GL/glut.h>

// Global access to things related to drawing.
namespace CLI_Global {

	struct Pixel {
		GLubyte R;
		GLubyte G;
		GLubyte B;
	};

	extern int imageWidth, imageHeight;
	extern Pixel * imageArray;

	// Resize the image, clearing any pixels that have been set.
	void resizeImage(int width, int height);

	// Retrieves a pointer to a pixel in the buffer.
	Pixel * getPixel(int row, int col);

	// Set a pixel to a certain RGB color.
	void setPixel(int row, int col, Pixel p);

}

#endif
