#include "reset_module.h"
#include "cli_pipeline.h"
#include "cli_global.h"
#include <armadillo>

CLI_Reset::~CLI_Reset()
{
}

using namespace CLI_Pipeline;
using namespace CLI_Global;
using namespace arma;

void CLI_Reset::execute(std::vector<char *> &params)
{
	std::cout << "Clearing the screen and all projection matrices." << std::endl;

	while (transform_stack.size() > 0)
		transform_stack.pop_back();

	transform_stack.push_back(eye<fmat>(4, 4));

	orth.eye();
	perspect.eye();
	camera.eye();

	clearImage();

	glutPostRedisplay();
}
