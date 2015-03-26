#include "vertex_module.h"
#include "geometry_utils.h"
#include <iostream>

CLI_Vertex::~CLI_Vertex()
{
}

void CLI_Vertex::execute(std::vector<char *> &params)
{
	float x = CLI_Module::parseNumericalArg(params[0]);
	float y = CLI_Module::parseNumericalArg(params[1]);
	float z = CLI_Module::parseNumericalArg(params[2]);

	CLI_Geometry::gtVertex3f(x, y, z);

	std::cout << "Vertex at x=" << x << ",y=" << y << ",z=" << z << std::endl;;
}
