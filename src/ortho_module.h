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
    virtual const char * getHelp() { return "ortho l,r,b,t,n,f: does an orthographic projection along the z-axis. The six parameters specify the dimensions of a box to which all lines will be clipped. l and r are the minimum and maximum x values that are mapped to the left and right edges of the window; b and t specify the min a max y values that are mapped to the top and bottom of the window; n and f specify the closest and farthest z values that are drawn. The camera faces the negatvie z-axis."; }
};

#endif
