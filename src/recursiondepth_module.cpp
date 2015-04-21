#include "recursiondepth_module.h"
#include "cli_raytrace.h"
CLI_Recursiondepth::~CLI_Recursiondepth()
{
}

void CLI_Recursiondepth::execute(std::vector<char *> &params)
{
	CLI_Raytrace::max_recursion_depth = (int) parseNumericalArg(params[0]);

	std::cout << "Using max recursion depth of " << CLI_Raytrace::max_recursion_depth << std::endl;
}
