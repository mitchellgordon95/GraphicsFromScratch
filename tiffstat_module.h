#ifndef TIFFSTAT_MODULE_H
#define TIFFSTAT_MODULE_H 

#include "cli_module.h"

// Implements the draw command for the cli
class CLI_TiffStat : public CLI_Module 
{
private:
    // TiffStats the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_TiffStat(): CLI_Module("tiffstat", 1) {};
    ~CLI_TiffStat();
};

#endif
