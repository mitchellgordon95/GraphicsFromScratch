#include "cli_module.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

bool CLI_Module::interpret(std::vector<char *> &command)
{
    if (command.size() == 0 || strncmp(command[0], keyword, strlen(keyword)) != 0)
        return false;

    if (command.size() > 1 && strcmp(command[1], "help") == 0) {
    	std::cout << getHelp() << std::endl;
    	return true;
    }

    if ( command.size() - 1 < (size_t) param_count)
    {
        std::cout << "Invalid argument count. Expected at least " << param_count << " params." << std::endl;
        std::cout << "Enter '" << keyword << " help' to display usage." << std::endl;
    }
    else
    {
        command.erase(command.begin());

        try
        {
            execute(command);
        }
        catch (std::exception &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    return true;
}

// Parses a character string into a numerical argument.
float CLI_Module::parseNumericalArg(char * param) {
	char * endptr;
	float out = strtod(param, &endptr);

	// If endptr doesn't point to the end of the string
	// then there was part of the token we couldn't parse.
	if (*endptr != '\0')
	{
		throw std::invalid_argument("Could not parse numerical argument.");
	}

	return out;
}
