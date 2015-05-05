#ifndef TIFFWRITE_MODULE_H
#define TIFFWRITE_MODULE_H 

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_Tiffwrite : public CLI_Module 
{
private:
    // TiffWrites the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_Tiffwrite(): CLI_Module("tiffwrite", 5) {};
    ~CLI_Tiffwrite();
};

#endif
