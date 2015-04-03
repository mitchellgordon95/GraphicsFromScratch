#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include "cli_module.h"

// Implements the camera command for the cli
class CLI_Camera : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Camera(): CLI_Module("camera", 14) {};
    ~CLI_Camera();
    virtual const char * getHelp() { return "camera "; }
};

#endif
