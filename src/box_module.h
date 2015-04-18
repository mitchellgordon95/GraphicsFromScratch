#ifndef BOX_MODULE_H
#define BOX_MODULE_H

#include "cli_module.h"

// Implements the box command for the cli
class CLI_Box : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Box(): CLI_Module("box", 12) {};
    ~CLI_Box();
    virtual const char * getHelp() { return "box ux,uy,uz,vx,y,vz,ar,ag,ab,rr,rg,rb,[sr,sg,sb]: create an axis-aligned box. u is a corner of the box, v is the other corner, a is ambient color, r is reflective color, and s is specular color."; }
};

#endif
