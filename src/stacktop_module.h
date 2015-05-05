#ifndef STACKTOP_MODULE_H
#define STACKTOP_MODULE_H

#include "cli_module.h"

// Implements the stacktop command for the cli
class CLI_Stacktop : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Stacktop(): CLI_Module("stacktop", 0) {};
    ~CLI_Stacktop();
    virtual const char * getHelp() { return "prints the top matrix on the stack of transformation matrices"; }
};

#endif
