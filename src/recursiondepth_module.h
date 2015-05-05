#ifndef RECURSIONDEPTH_MODULE_H
#define RECURSIONDEPTH_MODULE_H

#include "cli_module.h"

// Implements the recursiondepth command for the cli
class CLI_Recursiondepth : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Recursiondepth(): CLI_Module("recursiondepth", 1) {};
    ~CLI_Recursiondepth();
    virtual const char * getHelp() { return "recursiondepth x: instructs the raytracer to recursively compute specular color x times."; }
};

#endif
