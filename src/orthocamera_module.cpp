#include "orthocamera_module.h"
#include "cli_raytrace.h"

CLI_Orthocamera::~CLI_Orthocamera()
{
}

void CLI_Orthocamera::execute(std::vector<char *> &params)
{
	CLI_Raytrace::orthographic = true;

	std::cout << "Using an orthographic camera for the raytracer." << std::endl;
}
