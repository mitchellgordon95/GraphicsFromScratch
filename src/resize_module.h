#ifndef RESIZE_MODULE_H
#define RESIZE_MODULE_H

#include "cli_module.h"

// Implements the resize command for the cli
class CLI_Resize : public CLI_Module
{
private:
    // Resizes the pen to a specified location in 3 dimensions
    virtual void execute(std::vector<char *> &params);
public:
    CLI_Resize(): CLI_Module("resize", 2) {};
    ~CLI_Resize();
};

#endif
