#include "printcamera_module.h"
#include <iostream>
#include "projection_global.h"

CLI_Printcamera::~CLI_Printcamera()
{
}

void CLI_Printcamera::execute(std::vector<char *> &params)
{
	std::cout << "Camera matrix: " << std::endl << CLI_Projection::camera << std::endl;
}
