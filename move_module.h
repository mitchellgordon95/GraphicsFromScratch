#ifndef MOVE_MODULE_H
#define MOVE_MODULE_H

#include "cli_module.h"

// Implements the move command for the cli
class CLI_Move : public CLI_Module 
{
public:
    CLI_Move();
    ~CLI_Move();

    // Moves the pen to a specified location in 3 dimensions
    bool execute(std::vector<char *> &command);
};

#endif
