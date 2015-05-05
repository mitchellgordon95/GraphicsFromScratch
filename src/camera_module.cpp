#include "camera_module.h"
#include "cli_raytrace.h"
#include <armadillo>

CLI_Camera::~CLI_Camera()
{
}

using namespace arma;
using namespace CLI_Raytrace;

void CLI_Camera::execute(std::vector<char *> &params)
{
	orthographic = false;

	viewpoint(0) = parseNumericalArg(params[0]);
	viewpoint(1) = parseNumericalArg(params[1]);
	viewpoint(2) = parseNumericalArg(params[2]);

	gaze_dir(0) = parseNumericalArg(params[3]);
	gaze_dir(1) = parseNumericalArg(params[4]);
	gaze_dir(2) = parseNumericalArg(params[5]);

	up_dir(0) = parseNumericalArg(params[6]);
	up_dir(1) = parseNumericalArg(params[7]);
	up_dir(2) = parseNumericalArg(params[8]);

	screen_dist = parseNumericalArg(params[9]);

	screen_bot_left(0) = parseNumericalArg(params[10]);
	screen_bot_left(1) = parseNumericalArg(params[11]);

	screen_top_right(0) = parseNumericalArg(params[12]);
	screen_top_right(1) = parseNumericalArg(params[13]);

	std::cout << "Using a camera perspective for the raytracer." << std::endl;
}
