#include "signal_utils.h"
#include "cli_global.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace CLI_Global;

Filter_Type globalFilterType = LANCZOS;
int globalFilterRadius = 3;

void setFilterType(Filter_Type type) {
	globalFilterType = type;
}

const char * getFilterName() {
	return getFilterName(globalFilterType);
}

const char * getFilterName(Filter_Type type) {
	switch (type) {
	case LANCZOS:
		return "Lanczos";
	case GAUSSIAN:
		return "Gaussian";
	case BOX:
		return "Box";
	case TENT:
		return "Tent";
	default:
		return "Unknown";
	}
}

void setFilterRadius(int radius) {
	globalFilterRadius = radius;
}

int getFilterRadius() {
	return globalFilterRadius;
}

float lanczosFilter(float x, float radius) {
	if (x == 0)
		return 1;
	else if (abs(x) < radius)
		return radius * sin(M_PI * x) * sin((M_PI * x) / radius) / pow(M_PI, 2) / pow(x, 2);
	else
		return 0;
}

// A normal gaussian function, centered at the origin, with a standard deviation of 1 pixel.
// Filter radius is not taken into account.
float gaussianFilter(float x, float radius) {
	return  exp(-pow(x, 2) / (2 * pow(radius, 2))) / sqrt(2 * M_PI * radius);
}

float boxFilter(float x, float radius) {
	if (abs(x) < radius)
		return 1 / (2 *radius);
	else
		return 0;
}

float tentFilter(float x, float radius) {
	if (abs(x) < radius)
		return (1 - abs(x / radius)) / radius;
	else
		return 0;
}

Filter_Func_Pointer makeFilter(Filter_Type type) {
	if (type == LANCZOS)
		return lanczosFilter;
	if (type == GAUSSIAN)
		return gaussianFilter;
	else if (type == BOX)
		return boxFilter;
	else if (type == TENT)
		return tentFilter;
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

			Pixel output_pixel = {0, 0, 0};
			float norm = 0;

			for (int k = lower; k < upper; ++k) {
				float filter_val = filter(k - x, radius);
				norm += filter_val;
				Pixel * p = CLI_Global::getPixel(row, k, in);

				output_pixel = output_pixel + (*p * filter_val);
			}

			// Normalize the result
			output_pixel = output_pixel / norm;

			// Clamp to [0, 1]
			clamp(output_pixel);

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

			Pixel output_pixel = {0,0,0};
			float norm = 0;

			for (int k = lower; k < upper; ++k) {
				float filter_val = filter(k - x, radius);
				norm += filter_val;
				Pixel * p = CLI_Global::getPixel(k, col, in);

				output_pixel = output_pixel + (*p * filter_val);
			}

			// Normalize the result
			output_pixel = output_pixel / norm;


			// Clamp to [0, 1]
			clamp(output_pixel);

			// Assign the pixel to the output image.
			CLI_Global::setPixel(row, col, output_pixel, out);
	}

	return out;
}

Image resample(Image in, int width, int height) {
	return resample(in, width, height, globalFilterType, globalFilterRadius);
}

Image resample(Image in, int width, int height, Filter_Type filter_type, int radius) {
	Filter_Func_Pointer filter = makeFilter(filter_type);

	Image tmp = resampleX(in, width, filter, radius);
	Image out = resampleY(tmp, height, filter, radius);

	return out;

}
