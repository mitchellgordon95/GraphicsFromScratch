#ifndef ILIGHT_MODULE_H
#define ILIGHT_MODULE_H

#include "cli_module.h"

// Implements the ilight command for the cli
class CLI_Ilight : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Ilight(): CLI_Module("ilight", 6) {};
    ~CLI_Ilight();
    virtual const char * getHelp() { return "ilight lr,lg,lb,dx,dy,dz"; }
};

#endif
