#ifndef SIGNAL_UTILS_H
#define SIGNAL_UTILS_H
#include <stdint.h>
#include <exception>
#include <stdexcept>
#include "cli_global.h"

using namespace CLI_Global;

// Types of convolution filters
enum Filter_Type { LANCZOS, GAUSSIAN, BOX, TENT };

// A pointer to a filter function
typedef float (*Filter_Func_Pointer)(float x, float radius);

// Returns a convolution filter
Filter_Func_Pointer makeFilter(Filter_Type type);

// Sets the default filter used by the functions in this package
void setFilterType(Filter_Type type);
void setFilterType(char * type);

// Returns the string name for the selected filter
const char * getFilterName();

// Returns the string name for the filter type
const char * getFilterName(Filter_Type type);

// Sets the default radius of the filter used by functions in this package.
void setFilterRadius(int radius);
int getFilterRadius();

// Resamples an image with a new pixel width and height. Use the globally selected filter.
Image resample (Image in, int width, int height);

// Resamples an image with the specified filter and radius.
Image resample (Image in, int width, int height, Filter_Type filter_type, int radius);

#endif
