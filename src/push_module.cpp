#include "push_module.h"
#include "geometry_utils.h"

CLI_Push::~CLI_Push()
{
}

using namespace CLI_Geometry;

void CLI_Push::execute(std::vector<char *> &params)
{
	transform_stack.push_back(transform_stack.back());
	std::cout << "Pushed a copy of the top element onto the transform stack." << std::endl;
}
