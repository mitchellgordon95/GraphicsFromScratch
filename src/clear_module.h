#ifndef CLEAR_MODULE_H
#define CLEAR_MODULE_H

#include "cli_module.h"

// Implements the clear command for the cli
class CLI_Clear : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Clear(): CLI_Module("clear", 0) {};
    ~CLI_Clear();
    virtual const char * getHelp() { return "clear the screen and object lists"; }
};

#endif
