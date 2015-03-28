#ifndef ORIENT_MODULE_H
#define ORIENT_MODULE_H

#include "cli_module.h"

// Implements the orient command for the cli
class CLI_Orient : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Orient(): CLI_Module("orient", 9) {};
    ~CLI_Orient();
    virtual const char * getHelp() { return "orient 00,01,02,10,11,12,20,21,22: adds a transform to the stack using the 3x3 matrix provided"; }
};

#endif
