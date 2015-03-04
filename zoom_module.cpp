#include "zoom_module.h"
#include "signal_utils.h"
#include <stdexcept>

using namespace CLI_Global;

CLI_Zoom::~CLI_Zoom()
{
}

void CLI_Zoom::execute(std::vector<char *> &params)
{
	std::vector<char *> newCommand;
	newCommand.push_back("resize");
	newCommand.push_back(params[0]);
	newCommand.push_back(params[0]);
	dispatcher.interpret(newCommand);
}
