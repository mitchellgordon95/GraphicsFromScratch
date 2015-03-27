#ifndef SCALE_MODULE_H
#define SCALE_MODULE_H

#include "cli_module.h"

// Implements the scale command for the cli
class CLI_Scale : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Scale(): CLI_Module("scale", 3) {};
    ~CLI_Scale();
    virtual const char * getHelp() { return "scale sx, sy, xz: transforms the top matrix on the stack by scaling it."; }
};

#endif
