#ifndef PRINTPERSPECT_MODULE_H
#define PRINTPERSPECT_MODULE_H

#include "cli_module.h"

// Implements the printperspect command for the cli
class CLI_Printperspect : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Printperspect(): CLI_Module("printperspect", 0) {};
    ~CLI_Printperspect();
    virtual const char * getHelp() { return "prints the matrix associated with the perspective projection"; }
};

#endif
