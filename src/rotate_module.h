#ifndef ROTATE_MODULE_H
#define ROTATE_MODULE_H

#include "cli_module.h"

// Implements the rotate command for the cli
class CLI_Rotate : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Rotate(): CLI_Module("rotate", 4) {};
    ~CLI_Rotate();
    virtual const char * getHelp() { return "rotate theta, x, y, z: adds a rotation of theta degrees counterclockwise, as one looks from the point (x, y, z) toward the origin"; }
};

#endif
