#include "stacktop_module.h"
#include "projection_global.h"
#include <armadillo>
#include <iostream>

CLI_Stacktop::~CLI_Stacktop()
{
}

using namespace CLI_Projection;
using namespace arma;

void CLI_Stacktop::execute(std::vector<char *> &params)
{
	fmat top = transform_stack.back();

	std::cout << top << std::endl;

}
