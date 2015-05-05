#ifndef LOOKAT_MODULE_H
#define LOOKAT_MODULE_H

#include "cli_module.h"

// Implements the lookat command for the cli
class CLI_Lookat : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Lookat(): CLI_Module("lookat", 9) {};
    ~CLI_Lookat();
    virtual const char * getHelp() { return "lookat fx,fy,fz,ax,ay,az,ux,uy,uz: changes the point of view. Looks from point f, at point a, with the up direction given by vector u."; }
};

#endif
