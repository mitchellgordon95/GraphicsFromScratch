#ifndef PRINTORTHO_MODULE_H
#define PRINTORTHO_MODULE_H

#include "cli_module.h"

// Implements the printortho command for the cli
class CLI_Printortho : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Printortho(): CLI_Module("printortho", 0) {};
    ~CLI_Printortho();
    virtual const char * getHelp() { return "Prints the matrix associated with the orthographic projection"; }
};

#endif
