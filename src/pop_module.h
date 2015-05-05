#ifndef POP_MODULE_H
#define POP_MODULE_H

#include "cli_module.h"

// Implements the pop command for the cli
class CLI_Pop : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Pop(): CLI_Module("pop", 0) {};
    ~CLI_Pop();
    virtual const char * getHelp() { return "Pops a matrix off the top of the transform stack."; }
};

#endif
