#ifndef SCREEN_MODULE_H
#define SCREEN_MODULE_H

#include "cli_module.h"

// Implements the screen command for the cli
class CLI_Screen : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Screen(): CLI_Module("screen", 2) {};
    ~CLI_Screen();
    virtual const char * getHelp() { return "Set the screen dimension"; }
};

#endif
