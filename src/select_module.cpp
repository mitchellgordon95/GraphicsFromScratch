#include "select_module.h"
#include "signal_utils.h"
#include <stdexcept>
#include <string.h>
#include <iostream>

using namespace CLI_Global;

CLI_Select::~CLI_Select()
{
}

const char * CLI_Select::getHelp() {
   	return "Usage: select [filter name] [filter pixel radius]\n"
    			"Known filters are Lanczos, Gaussian, Box, and Tent";
}

void CLI_Select::execute(std::vector<char *> &params)
{
	char * filter_name = params[0];

	for (size_t i = 0; i < strlen(filter_name); ++i)
		filter_name[i] = tolower(filter_name[i]);

	if (strcmp(filter_name, "lanczos") == 0)
		setFilterType(LANCZOS);
	else if (strcmp(filter_name, "gaussian") == 0)
			setFilterType(GAUSSIAN);
	else if (strcmp(filter_name, "box") == 0)
			setFilterType(BOX);
	else if (strcmp(filter_name, "tent") == 0)
			setFilterType(TENT);
	else
		throw std::runtime_error("Unknown filter type.");

	if (params.size() > 1) {
		 setFilterRadius(parseNumericalArg(params[1]));
	}

	std::cout << "Using a " << getFilterName() << " filter with a " << getFilterRadius() << "px radius." << std::endl;

}
