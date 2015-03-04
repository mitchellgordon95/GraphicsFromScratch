#include "signal_utils.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

// A gaussian function, centered at the origin
float gaussianFilter(float x) {
	return (1 / sqrt(2 * M_PI)) * exp(-pow(x, 2) / 2);
}

float pointFilter(float x) {
	if (x == 0)
		return 1;
	else
		return 0;
}

Filter_Func_Pointer makeFilter(Filter_Type type) {
	if (type == GAUSSIAN)
		return gaussianFilter;
	else if (type == POINT)
		return pointFilter;
	else
		throw std::runtime_error("Unknown filter type.");
}

Image resampleX(Image in, int newWidth, Filter_Func_Pointer filter, int radius) {

	Image out = CLI_Global::createImage(newWidth, in.height);

	// We're going to take samples distributed evenly through the input image from left to right.
	float spacing = (float) in.width / newWidth;
	float first_sample = spacing / 2;

	// For each row in the input and column in the output.
	for (int row = 0; row < in.height; ++row)
		for (int col = 0; col < newWidth; ++col) {
			// Reconstruct the analog input image using a convolution filter
			// at the new sample point, x
			float x = first_sample + col * spacing;

			// Calculate upper and lower bounds for applying the filter.
			int lower = (int) (x - radius);
			int upper = (int) (x + radius + 1);

			// Clamp to the border. Assume values outside are 0.
			lower = (lower >= 0) ? lower : 0;
			upper = (upper <= in.width) ? upper : in.width;

			Pixel output_pixel = { 0, 0, 0 };

			for (int k = lower; k < upper; ++k) {
				float filter_val = filter(k - x);
				Pixel * p = CLI_Global::getPixel(row, k, in);

				output_pixel.R += (GLubyte) (p->R * filter_val);
				output_pixel.G += (GLubyte) (p->G * filter_val);
				output_pixel.B += (GLubyte) (p->B * filter_val);
			}

			// Assign the pixel to the output image.
			CLI_Global::setPixel(row, col, output_pixel, out);
	}

	return out;
}

Image resampleY(Image in, int newHeight, Filter_Func_Pointer filter, int radius) {
	Image out = CLI_Global::createImage(in.width, newHeight);

	// We're going to take samples distributed evenly through the input image from top to bottom
	float spacing = (float) in.height / newHeight;
	float first_sample = spacing / 2;

	// For each row in the output and column in the input.
	for (int row = 0; row < newHeight; ++row)
		for (int col = 0; col < in.width; ++col) {
			// Reconstruct the analog input image using a convolution filter
			// at the new sample point, x. Apply the filter vertically.
			float x = first_sample + row * spacing;

			// Calculate upper and lower bounds for applying the filter.
			int lower = (int) (x - radius);
			int upper = (int) (x + radius + 1);

			// Clamp to the border. Assume values outside are 0.
			lower = (lower >= 0) ? lower : 0;
			upper = (upper <= in.height) ? upper : in.height;

			Pixel output_pixel = { 0, 0, 0 };

			for (int k = lower; k < upper; ++k) {
				float filter_val = filter(k - x);
				Pixel * p = CLI_Global::getPixel(k, col, in);

				output_pixel.R += (GLubyte) (p->R * filter_val);
				output_pixel.G += (GLubyte) (p->G * filter_val);
				output_pixel.B += (GLubyte) (p->B * filter_val);
			}

			// Assign the pixel to the output image.
			CLI_Global::setPixel(row, col, output_pixel, out);
	}

	return out;
}

Image resample(Image in, int width, int height, Filter_Type filter_type,
		int radius) {
	Filter_Func_Pointer filter = makeFilter(filter_type);

	Image tmp = resampleX(in, width, filter, radius);
	Image out = resampleY(tmp, height, filter, radius);

	return out;

}
