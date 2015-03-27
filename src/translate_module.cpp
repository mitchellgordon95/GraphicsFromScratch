#include "translate_module.h"
#include "projection_global.h"
#include <armadillo>

CLI_Translate::~CLI_Translate()
{
}

using namespace CLI_Projection;
using namespace arma;

void CLI_Translate::execute(std::vector<char *> &params)
{
	float x = CLI_Module::parseNumericalArg(params[0]);
	float y = CLI_Module::parseNumericalArg(params[1]);
	float z = CLI_Module::parseNumericalArg(params[2]);

	std::cout << "Translating the top matrix by " << x << ", " << y << ", " << z << std::endl;

	fmat trans = eye<fmat>(4, 4);
	trans.at(0, 3) = x;
	trans.at(1, 3) = y;
	trans.at(2, 3) = z;

	fmat c = transform_stack.back();

	c *= trans;

	transform_stack.pop_back();
	transform_stack.push_back(c);

}
