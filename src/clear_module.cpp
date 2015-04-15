#include "clear_module.h"
#include "cli_raytrace.h"
#include "cli_global.h"

CLI_Clear::~CLI_Clear()
{
}

void CLI_Clear::execute(std::vector<char *> &params)
{
	CLI_Raytrace::surfaces.clear();
	CLI_Global::clearImage();
}
