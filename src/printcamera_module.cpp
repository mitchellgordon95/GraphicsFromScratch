#include "printcamera_module.h"
#include <iostream>
#include "cli_pipeline.h"

CLI_Printcamera::~CLI_Printcamera()
{
}

void CLI_Printcamera::execute(std::vector<char *> &params)
{
	std::cout << "Camera matrix: " << std::endl << CLI_Pipeline::camera << std::endl;
}
