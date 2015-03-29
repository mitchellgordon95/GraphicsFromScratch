#include "diagnostics_module.h"
#include "cli_global.h"
#include <string.h>
#include <iostream>

CLI_Diagnostics::~CLI_Diagnostics()
{
}

void CLI_Diagnostics::execute(std::vector<char *> &params)
{
	if (strncmp(params[0], "on", 2) == 0) {
		CLI_Global::diagnostics = true;
		std::cout << "Diagnostics on." << std::endl;
	}
	else if (strncmp(params[0], "off", 3) == 0) {
		CLI_Global::diagnostics = false;
		std::cout << "Diagnostics off." << std::endl;
	}
	else
		std::cout << "Not a valid option. Use on or off." << std::endl;
}
