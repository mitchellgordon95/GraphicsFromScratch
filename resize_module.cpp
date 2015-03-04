#include "resize_module.h"
#include "signal_utils.h"
#include <iostream>

using namespace CLI_Global;

CLI_Resize::~CLI_Resize()
{
}

void CLI_Resize::execute(std::vector<char *> &params)
{
	float xScale = CLI_Module::parseNumericalArg(params[0]);
	float yScale = CLI_Module::parseNumericalArg(params[1]);

	int newX = (int)(xScale * displayImage.width);
	int newY = (int)(yScale * displayImage.height);

	Image newImage = resample(displayImage, newX, newY, GAUSSIAN, 5);

	deleteImage(displayImage);
	displayImage = newImage;

	glutPostRedisplay();
	glutReshapeWindow(newX, newY);

	std::cout << "Resizing the image to " << newX << "x" << newY << "." << std::endl;
	std::cout << "Applying a 5px Gaussian filter for anti-aliasing" << std::endl;
}
