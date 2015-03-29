#include "ortho_module.h"
#include "projection_global.h"
#include <iostream>

CLI_Ortho::~CLI_Ortho()
{
}

using namespace CLI_Projection;
using namespace arma;

void CLI_Ortho::execute(std::vector<char *> &params)
{
	float left = CLI_Module::parseNumericalArg(params[0]);
	float right = CLI_Module::parseNumericalArg(params[1]);
	float bottom = CLI_Module::parseNumericalArg(params[2]);
	float top = CLI_Module::parseNumericalArg(params[3]);
	float near = CLI_Module::parseNumericalArg(params[4]);
	float far = CLI_Module::parseNumericalArg(params[5]);

	// Make sure near and far are negative
	near = (near > 0) ? -near : near;
	far = (far > 0) ? -far : far;

	updateOrth(left, right, bottom, top, near, far);

}
