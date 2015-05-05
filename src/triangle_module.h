#ifndef TRIANGLE_MODULE_H
#define TRIANGLE_MODULE_H

#include "cli_module.h"

// Implements the triangle command for the cli
class CLI_Triangle : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Triangle(): CLI_Module("triangle", 15) {};
    ~CLI_Triangle();
    virtual const char * getHelp() { return "triangle ux,uy,uz,vx,vy,vz,wx,wy,wz,ar,ag,ab,rr,rg,rb[sr,sg,sb]: create a triangle with vertices u,v,w. Ambient color is a, reflective color is r, and specular color is s."; }
};

#endif
