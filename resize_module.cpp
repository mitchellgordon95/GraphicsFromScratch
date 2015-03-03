#include "resize_module.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>

CLI_Resize::~CLI_Resize()
{
}

void CLI_Resize::execute(std::vector<char *> &params)
{
	float xScale = CLI_Module::parseNumericalArg(params[0]);
	float yScale = CLI_Module::parseNumericalArg(params[1]);


}
