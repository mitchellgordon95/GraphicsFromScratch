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

	near = -near;
	far = -far;

	orth = eye<fmat>(4,4);

	orth(0,0) = 2 / (right - left);
	orth(1,1) = 2 / (top - bottom);
	orth(2,2) = 2 / (near - far);
	orth(0,3) = - (right + left) / (right - left);
	orth(1,3) = - (top + bottom) / (top - bottom);
	orth(2,3) = - (near + far) / (near - far);

	std::cout << "Updated orthographic project matrix: l=" << left;
	std::cout << ",r=" << right << ",b=" << bottom << ",t=" << top;
	std::cout << ",n=" << near << ",f=" << far << std::endl;

}
