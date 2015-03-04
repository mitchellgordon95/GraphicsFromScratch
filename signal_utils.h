#ifndef SIGNAL_UTILS_H
#define SIGNAL_UTILS_H
#include <stdint.h>
#include <exception>
#include <stdexcept>
#include "cli_global.h"

using namespace CLI_Global;

// Types of convolution filters
enum Filter_Type { GAUSSIAN, POINT };

// A pointer to a filter function
typedef float (*Filter_Func_Pointer)(float);

// Returns a convolution filter
Filter_Func_Pointer getFilter(Filter_Type type);

// Resamples an image with a new pixel width and height.
Image resample (Image in, int width, int height, Filter_Type type, int radius);

#endif
