#ifndef BACKGROUND_MODULE_H
#define BACKGROUND_MODULE_H

#include "cli_module.h"

// Implements the background command for the cli
class CLI_Background : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Background(): CLI_Module("background", 3) {};
    ~CLI_Background();
    virtual const char * getHelp() { return "background r,g,b: set the background color"; }
};

#endif
