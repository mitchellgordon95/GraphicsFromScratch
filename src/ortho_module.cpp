#include "ortho_module.h"
#include "geometry_utils.h"
#include <iostream>

CLI_Ortho::~CLI_Ortho()
{
}

using namespace CLI_Geometry;

void CLI_Ortho::execute(std::vector<char *> &params)
{
	float left = CLI_Module::parseNumericalArg(params[0]);
	float right = CLI_Module::parseNumericalArg(params[1]);
	float bottom = CLI_Module::parseNumericalArg(params[2]);
	float top = CLI_Module::parseNumericalArg(params[3]);
	float near = CLI_Module::parseNumericalArg(params[4]);
	float far = CLI_Module::parseNumericalArg(params[5]);

	// Bobby's code assumes near and far are negated
	near = -near;
	far = -far;

	orth = Identity;

	orth.mat[0][0] = 2 / (right - left);
	orth.mat[1][1] = 2 / (top - bottom);
	orth.mat[2][2] = 2 / (near - far);
	orth.mat[0][3] = - (right + left) / (right - left);
	orth.mat[1][3] = - (top + bottom) / (top - bottom);
	orth.mat[2][3] = - (near + far) / (near - far);

	std::cout << "Updated orthographic project matrix: l=" << left;
	std::cout << ",r=" << right << ",b=" << bottom << ",t=" << top;
	std::cout << ",n=" << near << ",f=" << far << std::endl;

}
