#include "orient_module.h"
#include "cli_pipeline.h"
#include <armadillo>

CLI_Orient::~CLI_Orient()
{
}

using namespace CLI_Pipeline;
using namespace arma;

void CLI_Orient::execute(std::vector<char *> &params)
{
	float a = CLI_Module::parseNumericalArg(params[0]);
	float b = CLI_Module::parseNumericalArg(params[1]);
	float c = CLI_Module::parseNumericalArg(params[2]);
	float d = CLI_Module::parseNumericalArg(params[3]);
	float e = CLI_Module::parseNumericalArg(params[4]);
	float f = CLI_Module::parseNumericalArg(params[5]);
	float g = CLI_Module::parseNumericalArg(params[6]);
	float h = CLI_Module::parseNumericalArg(params[7]);
	float i = CLI_Module::parseNumericalArg(params[8]);

	fmat trans = eye<fmat>(4,4);

	fmat smaller;
	smaller << a << b << c
			<< d << e << f
			<< g << h << i;

	trans.submat(0,0,2,2) = smaller;

	fmat current = transform_stack.back();
	transform_stack.pop_back();
	transform_stack.push_back(current * trans);
}
