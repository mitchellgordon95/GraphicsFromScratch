#ifndef ZOOM_MODULE_H
#define ZOOM_MODULE_H

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_Zoom: public CLI_Module
{
private:
    // Draws the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_Zoom(): CLI_Module("zoom", 1) {};
    ~CLI_Zoom();
};

#endif
