#include "lookat_module.h"
#include "geometry_utils.h"
CLI_Lookat::~CLI_Lookat()
{
}

void CLI_Lookat::execute(std::vector<char *> &params)
{
	float fx = CLI_Module::parseNumericalArg(params[0]);
	float fy = CLI_Module::parseNumericalArg(params[1]);
	float fz = CLI_Module::parseNumericalArg(params[2]);
	float ax = CLI_Module::parseNumericalArg(params[3]);
	float ay = CLI_Module::parseNumericalArg(params[4]);
	float az = CLI_Module::parseNumericalArg(params[5]);
	float ux = CLI_Module::parseNumericalArg(params[6]);
	float uy = CLI_Module::parseNumericalArg(params[7]);
	float uz = CLI_Module::parseNumericalArg(params[8]);

	CLI_Geometry::gtLookAt(fx, fy, fz, ax, ay, az, ux, uy, uz);
}
