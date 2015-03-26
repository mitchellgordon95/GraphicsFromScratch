#ifndef TRANSLATE_MODULE_H
#define TRANSLATE_MODULE_H

#include "cli_module.h"

// Implements the translate command for the cli
class CLI_Translate : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Translate(): CLI_Module("translate", 3) {};
    ~CLI_Translate();
    virtual const char * getHelp() { return "translate x, y, z: adds a translation to the top element on the transformation stack"; }
};

#endif
