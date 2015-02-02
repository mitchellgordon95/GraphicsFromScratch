#ifndef TIFFREAD_MODULE_H
#define TIFFREAD_MODULE_H 

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_TiffRead : public CLI_Module 
{
private:
    // TiffReads the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_TiffRead(): CLI_Module("tiffread", 1) {};
    ~CLI_TiffRead();
};

#endif
