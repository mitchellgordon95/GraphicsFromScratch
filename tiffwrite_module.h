#ifndef TIFFWRITE_MODULE_H
#define TIFFWRITE_MODULE_H 

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_TiffWrite : public CLI_Module 
{
private:
    // TiffWrites the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_TiffWrite(): CLI_Module("tiffwrite", 1) {};
    ~CLI_TiffWrite();
};

#endif
