#include "triangle_module.h"
#include "cli_raytrace.h"
#include <armadillo>

CLI_Triangle::~CLI_Triangle()
{
}

using namespace CLI_Raytrace;
using namespace arma;

void CLI_Triangle::execute(std::vector<char *> &params)
{
	fvec a(3), b(3), c(3);

	a(0) = parseNumericalArg(params[0]);
	a(1) = parseNumericalArg(params[1]);
	a(2) = parseNumericalArg(params[2]);

	b(0) = parseNumericalArg(params[3]);
	b(1) = parseNumericalArg(params[4]);
	b(2) = parseNumericalArg(params[5]);

	c(0) = parseNumericalArg(params[6]);
	c(1) = parseNumericalArg(params[7]);
	c(2) = parseNumericalArg(params[8]);

	Pixel amb;
	amb.R = parseNumericalArg(params[9]);
	amb.G = parseNumericalArg(params[10]);
	amb.B = parseNumericalArg(params[11]);

	Pixel reflec;
	reflec.R = parseNumericalArg(params[12]);
	reflec.G = parseNumericalArg(params[13]);
	reflec.B = parseNumericalArg(params[14]);

	Pixel spec;
	if (params.size() == 18) {
		spec.R = parseNumericalArg(params[15]);
		spec.G = parseNumericalArg(params[16]);
		spec.B = parseNumericalArg(params[17]);
	}
	else { spec = {0,0,0}; }

	surfaces.push_back(new Triangle(a, b, c, amb, reflec, spec));

	std::cout << "Created a triangle with vertices: " << std::endl << a << b << c;
}
