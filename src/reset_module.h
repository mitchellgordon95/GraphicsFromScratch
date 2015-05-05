#ifndef RESET_MODULE_H
#define RESET_MODULE_H

#include "cli_module.h"

// Implements the reset command for the cli
class CLI_Reset : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Reset(): CLI_Module("reset", 0) {};
    ~CLI_Reset();
    virtual const char * getHelp() { return "reset: clears the screen and the transformation stack"; }
};

#endif
