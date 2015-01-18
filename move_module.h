#ifndef MOVE_MODULE_H
#define MOVE_MODULE_H

#include "cli_module.h"

// Implements the move command for the cli
class CLI_Move : public CLI_Module 
{
private:
    // Moves the pen to a specified location in 3 dimensions
    virtual bool execute(std::vector<char *> &params);
public:
    CLI_Move(): CLI_Module("move", 3) {};
    ~CLI_Move();
};

#endif
