#include "perspective_module.h"
#include "projection_global.h"
#include "cli_global.h"
#include <iostream>
#include <armadillo>

CLI_Perspective::~CLI_Perspective()
{
}

using namespace arma;
using namespace CLI_Projection;
using namespace CLI_Global;

void CLI_Perspective::execute(std::vector<char *> &params)
{
	float fov = CLI_Module::parseNumericalArg(params[0]);
	float aspect = CLI_Module::parseNumericalArg(params[1]);
	float near = CLI_Module::parseNumericalArg(params[2]);
	float far = CLI_Module::parseNumericalArg(params[3]);

	// Make sure near and far are negative
	near = (near > 0) ? -near : near;
	far = (far > 0) ? -far : far;

	perspect = zeros<fmat>(4,4);

	perspect(0,0) = near;
	perspect(1,1) = near;
	perspect(2,2) = near + far;
	perspect(2,3) = -far;
	perspect(3,2) = 1;

	if (diagnostics)
		std::cout << "Perspective Matrix: " << std::endl << perspect << std::endl;

	// Figure out the parameters for the following orthographic projection.
	float top = -near * tan(fov * M_PI / 360);
	float bottom = -top;
	float left = bottom * aspect;
	float right = top * aspect;

	updateOrth(left, right, bottom, top, near, far);
}
