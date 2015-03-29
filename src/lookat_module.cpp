#include "lookat_module.h"
#include "projection_global.h"
#include "cli_global.h"
#include <armadillo>

CLI_Lookat::~CLI_Lookat()
{
}

using namespace arma;
using namespace CLI_Projection;
using namespace CLI_Global;

void CLI_Lookat::execute(std::vector<char *> &params)
{
	// Note: f = from, a = at, u = up vector.
	float fx = CLI_Module::parseNumericalArg(params[0]);
	float fy = CLI_Module::parseNumericalArg(params[1]);
	float fz = CLI_Module::parseNumericalArg(params[2]);
	float ax = CLI_Module::parseNumericalArg(params[3]);
	float ay = CLI_Module::parseNumericalArg(params[4]);
	float az = CLI_Module::parseNumericalArg(params[5]);
	float ux = CLI_Module::parseNumericalArg(params[6]);
	float uy = CLI_Module::parseNumericalArg(params[7]);
	float uz = CLI_Module::parseNumericalArg(params[8]);

	// First, we translate the eye point to the origin.
	fmat translate = eye<fmat>(4,4);
	translate(0, 3) = -fx;
	translate(1, 3) = -fy;
	translate(2, 3) = -fz;

	// Then we rotate to a basis made using a->f and u. (the camera faces the negative z direction)
	frowvec up(3);
	up << ux << uy << uz;
	up = up / norm(up, 2);

	frowvec rotz(3);
	rotz << ax - fx
		 << ay - fy
	     << az - fz;
	rotz = rotz / norm(rotz, 2);

	frowvec rotx = cross (rotz, up);
	rotx = rotx / norm(rotx, 2);

	frowvec roty = cross(rotx, rotz);

	fmat rotate = eye<fmat>(4,4);

	rotate.submat(0, 0, 0, 2) = rotx;
	rotate.submat(1, 0, 1, 2) = roty;
	rotate.submat(2, 0, 2, 2) = -rotz;

	// The camera transform is simply a translate followed by a rotate.
	camera = rotate * translate;

	if (diagnostics) {
		std::cout << "Translate matrix" << std::endl << translate << std::endl;
		std::cout << "Rotate matrix" << std::endl << rotate << std::endl;
		std::cout << "Camera matrix (rotate * translate)" << std::endl << camera << std::endl;
	}
}
