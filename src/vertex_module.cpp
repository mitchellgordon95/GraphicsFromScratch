#include "vertex_module.h"
#include "cli_pipeline.h"
#include "cli_global.h"
#include <iostream>
#include <armadillo>
#include <GL/glut.h>

CLI_Vertex::~CLI_Vertex()
{
}

using namespace arma;
using namespace CLI_Pipeline;
using namespace CLI_Global;

void CLI_Vertex::execute(std::vector<char *> &params)
{
	float x = CLI_Module::parseNumericalArg(params[0]);
	float y = CLI_Module::parseNumericalArg(params[1]);
	float z = CLI_Module::parseNumericalArg(params[2]);

	if (!have_first) {
		first(0) = x;
		first(1) = y;
		first(2) = z;
		first(3) = 1;

		have_first = true;

		if (diagnostics)
			std::cout << "First vertex at x=" << x << ",y=" << y << ",z=" << z << std::endl;
	}
	else {
		second(0) = x;
		second(1) = y;
		second(2) = z;
		second(3) = 1;

		// Calculate the viewport transform
		fmat viewport = eye<fmat>(4,4);
		viewport(0,0) = (float) displayImage.width / 2;
		viewport(1,1) = (float) displayImage.height / 2;
		viewport(0,3) = ((float) displayImage.width + 1 )/ 2;
		viewport(1,3) = ((float) displayImage.height + 1) / 2;

		// Do the camera transform and perspective projection.
		fvec trans_first = viewport * orth * perspect * camera * transform_stack.back() * first;
		fvec trans_second = viewport * orth * perspect * camera * transform_stack.back() * second;

		// Change the homogeneous vectors into cartesian vectors
		trans_first = trans_first / trans_first(3);
		trans_second = trans_second / trans_second(3);

		draw_line(trans_first.at(0), trans_first.at(1), trans_second.at(0), trans_second.at(1));

		if (diagnostics) {
			std::cout << "Drew line to x=" << x << ",y=" << y << ",z=" << z << std::endl;
			std::cout << "(" << trans_second.at(0) << "," << trans_second.at(1) << "," << trans_second.at(2) << ") on screen" << std::endl;
		}

		glutPostRedisplay();

		have_first = false;
	}

}
