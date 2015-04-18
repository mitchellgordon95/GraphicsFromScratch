#include "box_module.h"
#include "cli_raytrace.h"
#include <armadillo>

CLI_Box::~CLI_Box()
{
}

using namespace CLI_Raytrace;
using namespace arma;

void CLI_Box::execute(std::vector<char *> &params)
{
	fvec llb(3), urt(3);

	llb(0) = parseNumericalArg(params[0]);
	llb(1) = parseNumericalArg(params[1]);
	llb(2) = parseNumericalArg(params[2]);

	urt(0) = parseNumericalArg(params[3]);
	urt(1) = parseNumericalArg(params[4]);
	urt(2) = parseNumericalArg(params[5]);

	Pixel amb;
	amb.R = parseNumericalArg(params[6]);
	amb.G = parseNumericalArg(params[7]);
	amb.B = parseNumericalArg(params[8]);

	Pixel reflec;
	reflec.R = parseNumericalArg(params[9]);
	reflec.G = parseNumericalArg(params[10]);
	reflec.B = parseNumericalArg(params[11]);

	Pixel spec;
	if (params.size() == 15) {
		spec.R = parseNumericalArg(params[12]);
		spec.G = parseNumericalArg(params[13]);
		spec.B = parseNumericalArg(params[14]);
	}
	else { spec = {0,0,0}; }

	surfaces.push_back(new Box(llb, urt, amb, reflec, spec));

	std::cout << "Created a box with one corner at " << std::endl << llb;
	std::cout << " and the other corner at " << std::endl << urt << ".";
}
