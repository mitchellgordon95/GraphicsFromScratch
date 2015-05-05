#ifndef DIAGNOSTICS_MODULE_H
#define DIAGNOSTICS_MODULE_H

#include "cli_module.h"

// Implements the diagnostics command for the cli
class CLI_Diagnostics : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Diagnostics(): CLI_Module("diagnostics", 1) {};
    ~CLI_Diagnostics();
    virtual const char * getHelp() { return "diagnostics [on|off]"; }
};

#endif
