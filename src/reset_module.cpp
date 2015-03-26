#include "reset_module.h"
#include "geometry_utils.h"
#include <armadillo>

CLI_Reset::~CLI_Reset()
{
}

using namespace CLI_Geometry;
using namespace arma;

void CLI_Reset::execute(std::vector<char *> &params)
{
	std::cout << "Clearing the screen." << std::endl;

	while (transform_stack.size() > 0)
		transform_stack.pop_back();

	transform_stack.push_back(eye<fmat>(4, 4));

	perspflag = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glFlush();
}
