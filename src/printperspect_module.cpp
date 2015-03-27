#include "printperspect_module.h"
#include <iostream>
#include "projection_global.h"

CLI_Printperspect::~CLI_Printperspect()
{
}

void CLI_Printperspect::execute(std::vector<char *> &params)
{
	std::cout << "Perspective matrix: " << std::endl << CLI_Projection::perspect << std::endl;
}
