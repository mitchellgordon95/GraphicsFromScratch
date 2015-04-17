#include "clear_module.h"
#include "cli_raytrace.h"
#include "cli_global.h"

CLI_Clear::~CLI_Clear()
{
}
using namespace CLI_Raytrace;

void CLI_Clear::execute(std::vector<char *> &params)
{
	for (size_t i = 0; i < surfaces.size(); ++i) {
		delete surfaces[i];
	}

	surfaces.clear();
	clearImage();
	glutPostRedisplay();
}
