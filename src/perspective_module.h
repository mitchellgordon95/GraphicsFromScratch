#ifndef PERSPECTIVE_MODULE_H
#define PERSPECTIVE_MODULE_H

#include "cli_module.h"

// Implements the perspective command for the cli
class CLI_Perspective : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Perspective(): CLI_Module("perspective", 4) {};
    ~CLI_Perspective();
    virtual const char * getHelp() { return "perspective fov, a, n, f: performs a perspective projection along the negative z-axis. fov is the field of view, a is the aspect ratio (the ratio of the viewing frustrum's width to its height. n and f specify near and far locations on the z-axis for clipping."; }
};

#endif
