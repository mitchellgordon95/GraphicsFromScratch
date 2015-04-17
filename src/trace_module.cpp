#include "trace_module.h"
#include "cli_raytrace.h"

CLI_Trace::~CLI_Trace()
{
}

using namespace CLI_Global;
using namespace CLI_Raytrace;
using namespace arma;

void CLI_Trace::execute(std::vector<char *> &params)
{
	if(orthographic) {
		// Shoot a ray straight through each pixel
		fvec point = zeros<fvec>(3);
		fvec dir = zeros<fvec>(3);
		dir(2) = -1;

		for (int row = 0; row < displayImage.height; ++row)
			for (int col = 0; col < displayImage.width; ++col){
				point(0) = col;
				point(1) = row;
				setPixel(row, col, shade(point, dir));
			}
	}
	else {

	}

	glutPostRedisplay();
}
