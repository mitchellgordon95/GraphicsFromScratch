#include "background_module.h"
#include "cli_raytrace.h"

CLI_Background::~CLI_Background()
{
}

void CLI_Background::execute(std::vector<char *> &params)
{
	float r = parseNumericalArg(params[0]);
	float g = parseNumericalArg(params[1]);
	float b = parseNumericalArg(params[2]);

	CLI_Raytrace::background = {r, g, b};

	std::cout << "Set background color to R=" << r << ",G=" << g << "B=" << b << std::endl;
}
