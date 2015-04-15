#include "ilight_module.h"
#include "cli_raytrace.h"

CLI_Ilight::~CLI_Ilight()
{
}

void CLI_Ilight::execute(std::vector<char *> &params)
{
	float cr = parseNumericalArg(params[0]);
	float cg = parseNumericalArg(params[1]);
	float cb = parseNumericalArg(params[2]);

	float dx = parseNumericalArg(params[3]);
	float dy = parseNumericalArg(params[4]);
	float dz = parseNumericalArg(params[5]);

	CLI_Raytrace::InfinityLight l;

	l.color = {cr, cg, cb};
	l.direction = arma::fvec(3);
	l.direction(0) = dx;
	l.direction(1) = dy;
	l.direction(2) = dz;

	CLI_Raytrace::lights.push_back(l);

	std::cout << "Created a light source at infinity with color (" << cr << "," << cg << ",";
	std::cout << cb << ") and direction (" << dx << "," << dy << "," << dz << ")" << std::endl;
}
