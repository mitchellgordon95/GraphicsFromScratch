#include "lookat_module.h"
#include "projection_global.h"
#include <armadillo>

CLI_Lookat::~CLI_Lookat()
{
}

using namespace arma;
using namespace CLI_Projection;

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

	// NOTE: This algorithm is directly translated from Bobby B's work. Not sure how it works.



}
