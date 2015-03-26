#ifndef PUSH_MODULE_H
#define PUSH_MODULE_H

#include "cli_module.h"

// Implements the push command for the cli
class CLI_Push : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Push(): CLI_Module("push", 0) {};
    ~CLI_Push();
    virtual const char * getHelp() { return "Pushes a copy of the top element onto the transform stack."; }
};

#endif
