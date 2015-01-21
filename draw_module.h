#ifndef DRAW_MODULE_H
#define DRAW_MODULE_H

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_Draw : public CLI_Module 
{
private:
    // Draws the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_Draw(): CLI_Module("draw", 3) {};
    ~CLI_Draw();
};

#endif
