#include "screen_module.h"
#include "cli_global.h"
#include <iostream>

CLI_Screen::~CLI_Screen()
{
}

void CLI_Screen::execute(std::vector<char *> &params)
{
	int x = (int) parseNumericalArg(params[0]);
	int y = (int) parseNumericalArg(params[1]);

	CLI_Global::resizeImage(x, y);

	std::cout << "Resized image to " << x << "x" << y << " pixels." << std::endl;

	glutPostRedisplay();
}
