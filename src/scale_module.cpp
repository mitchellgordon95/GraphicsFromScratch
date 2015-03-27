#include "scale_module.h"
#include "projection_global.h"
#include <armadillo>

CLI_Scale::~CLI_Scale()
{
}

using namespace CLI_Projection;

void CLI_Scale::execute(std::vector<char *> &params)
{
	float x = CLI_Module::parseNumericalArg(params[0]);
	float y = CLI_Module::parseNumericalArg(params[1]);
	float z = CLI_Module::parseNumericalArg(params[2]);

	std::cout << "Scaling the top matrix by " << x << ", " << y << ", " << z << std::endl;

	fmat trans = eye<fmat>(4, 4);
	trans.at(0, 0) = x;
	trans.at(1, 1) = y;
	trans.at(2, 2) = z;

	fmat c = transform_stack.back();

	c *= trans;

	transform_stack.pop_back();
	transform_stack.push_back(c);
}
