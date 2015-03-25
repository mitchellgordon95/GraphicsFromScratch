#ifndef SELECT_MODULE_H
#define SELECT_MODULE_H

#include "cli_module.h"

// Implements the select command for the cli
class CLI_Select: public CLI_Module
{
private:
    // Configures the filter that is used, globally.
    void execute(std::vector<char *> &params);
public:
    CLI_Select(): CLI_Module("select", 1) {};
    ~CLI_Select();

    const char * getHelp();
};

#endif
