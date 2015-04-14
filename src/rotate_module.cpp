#include "rotate_module.h"
#include "cli_pipeline.h"
#include <armadillo>

CLI_Rotate::~CLI_Rotate()
{
}

using namespace arma;
using namespace CLI_Pipeline;

void CLI_Rotate::execute(std::vector<char *> &params)
{
	float theta = CLI_Module::parseNumericalArg(params[0]);
	float x = CLI_Module::parseNumericalArg(params[1]);
	float y = CLI_Module::parseNumericalArg(params[2]);
	float z = CLI_Module::parseNumericalArg(params[3]);

	frowvec w(3);
	w(0) = x;
	w(1) = y;
	w(2) = z;

	// Construct an orthonormal basis using the vector w.
	w = w / norm(w, 2);

	// TODO - Is this an okay way to construct an orthonormal basis?

	int least = (w(0) < w(1)) ? 0 : 1;
	least = (w(least) < w(2)) ? least : 2;

	frowvec t = w;
	t(least) = 1;

	frowvec u = cross(w, t) / norm(cross(w, t), 2);
	frowvec v = cross(w, u);

	// Converts points with xyz basis to uvw basis
	fmat xyz_to_uvw = zeros<fmat>(3, 3);
	xyz_to_uvw.row(0) = u;
	xyz_to_uvw.row(1) = v;
	xyz_to_uvw.row(2) = w;

	// Construct a rotation about the third axis (z/w)
	fmat rotate = eye<fmat>(3, 3);
	float radians = theta * 2 * M_PI / 360;
	rotate(0, 0) = cos(radians);
	rotate(0, 1) = -sin(radians);
	rotate(1, 0) = sin(radians);
	rotate(1, 1) = cos(radians);

	fmat rotate_about_w = xyz_to_uvw.t() * rotate * xyz_to_uvw;

	fmat transform = eye<fmat>(4, 4);
	transform.submat(0, 0, 2, 2) = rotate_about_w;

	fmat c = transform_stack.back();

	transform_stack.pop_back();
	transform_stack.push_back(c * transform);

}
