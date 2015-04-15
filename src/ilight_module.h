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
    virtual const char * getHelp() { return "ilight cr,cg,cb,dx,dy,dz: adds a light at infinity. c is color, d is direction."; }
};

#endif
