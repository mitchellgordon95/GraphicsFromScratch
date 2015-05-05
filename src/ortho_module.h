#ifndef ORTHO_MODULE_H
#define ORTHO_MODULE_H

#include "cli_module.h"

// Implements the ortho command for the cli
class CLI_Ortho : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Ortho(): CLI_Module("ortho", 6) {};
    ~CLI_Ortho();
    virtual const char * getHelp() { return "ortho left,right,bottom,top,near,far: does an orthographic projection along the z-axis. The six parameters specify the dimensions of a box to which all lines will be clipped.";}
};

#endif
