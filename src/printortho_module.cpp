#include "printortho_module.h"
#include <iostream>
#include "cli_pipeline.h"

CLI_Printortho::~CLI_Printortho()
{
}

void CLI_Printortho::execute(std::vector<char *> &params)
{
	std::cout << "Orthographic Matrix: " << std::endl << CLI_Pipeline::orth << std::endl;
}
