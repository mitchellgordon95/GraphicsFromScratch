#include "sphere_module.h"
#include "cli_raytrace.h"

CLI_Sphere::~CLI_Sphere()
{
}

using namespace CLI_Raytrace;

void CLI_Sphere::execute(std::vector<char *> &params)
{
	float radius = parseNumericalArg(params[0]);

	fvec center(3);
	center(0) = parseNumericalArg(params[1]);
	center(1) = parseNumericalArg(params[2]);
	center(2) = parseNumericalArg(params[3]);

	Pixel amb;
	amb.R = parseNumericalArg(params[4]);
	amb.G = parseNumericalArg(params[5]);
	amb.B = parseNumericalArg(params[6]);

	Pixel reflec;
	reflec.R = parseNumericalArg(params[7]);
	reflec.G = parseNumericalArg(params[8]);
	reflec.B = parseNumericalArg(params[9]);

	Pixel spec;
	if (params.size() == 13) {
		spec.R = parseNumericalArg(params[10]);
		spec.G = parseNumericalArg(params[11]);
		spec.B = parseNumericalArg(params[12]);
	}
	else { spec = {0,0,0}; }

	surfaces.push_back(new Sphere(center, radius, amb, reflec, spec));

	std::cout << "Created a sphere with center " << std::endl << center << "and radius " << radius << std::endl;
}
