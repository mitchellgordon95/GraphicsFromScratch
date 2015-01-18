#ifndef COLOR_MODULE_H
#define COLOR_MODULE_H

#include "cli_module.h"

// Implements the color command for the cli
class CLI_Color : public CLI_Module 
{
private:
    // Sets the color of the pen 
    bool execute(std::vector<char *> &command);
public:
    CLI_Color(): CLI_Module("color", 3) {};
    ~CLI_Color();
};

#endif
