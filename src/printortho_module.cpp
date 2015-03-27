#include "printortho_module.h"
#include <iostream>
#include "projection_global.h"

CLI_Printortho::~CLI_Printortho()
{
}

void CLI_Printortho::execute(std::vector<char *> &params)
{
	std::cout << "Orthographic Matrix: " << std::endl << CLI_Projection::orth << std::endl;
}
