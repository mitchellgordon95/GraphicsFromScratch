#include "cli_module.h"
#include <string.h>
#include <vector>
#include <iostream>

bool CLI_Module::interpret(std::vector<char *> &command)
{
    if (command.size() == 0 || strncmp(command[0], keyword, strlen(keyword)) != 0)
        return false;

    std::cout << "In " << keyword << ": " ;

    if (command.size() - 1 != param_count)
    {
        std::cout << "Invalid argument count. Expected " << param_count << " params." << std::endl;
        return true;
    }

    command.erase(command.begin());

    return execute(command);
}
