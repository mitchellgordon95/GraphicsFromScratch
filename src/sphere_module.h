#ifndef SPHERE_MODULE_H
#define SPHERE_MODULE_H

#include "cli_module.h"

// Implements the sphere command for the cli
class CLI_Sphere : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Sphere(): CLI_Module("sphere", 10) {};
    ~CLI_Sphere();
    virtual const char * getHelp() { return "sphere R,cx,cy,cz,ar,ag,ab,rr,rg,rb,[sr,sg,sb]: create a sphere with radius R. c is center, a is ambient color, r is reflected color, and s is specular color"; }
};

#endif
