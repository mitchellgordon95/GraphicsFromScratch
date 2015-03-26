#include "zoom_module.h"
#include "signal_utils.h"
#include <stdexcept>
#include <string.h>

using namespace CLI_Global;

CLI_Zoom::~CLI_Zoom()
{
}

void CLI_Zoom::execute(std::vector<char *> &params)
{
	std::vector<char *> newCommand;
	newCommand.push_back(strdup("resize"));
	newCommand.push_back(params[0]);
	newCommand.push_back(params[0]);
	Dispatcher::getInstance().interpret(newCommand);
}
