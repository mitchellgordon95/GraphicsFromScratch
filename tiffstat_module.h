#ifndef TIFFSTAT_MODULE_H
#define TIFFSTAT_MODULE_H 

#include "cli_module.h"
#include "tiff_utils.h"
#include <stdint.h>
#include <fstream>
#include <map>

// Implements the draw command for the cli
class CLI_TiffStat : public CLI_Module 
{
private:
    // TiffStats the pen to a specified location in 3 dimensions
    void execute(std::vector<char *> &params);
public:
    CLI_TiffStat(): CLI_Module("tiffstat", 1) {};
    ~CLI_TiffStat();

    // Given a file, parse the TIFF IFD into structs
    // Can optionally be verbose and print metadata to console
    static std::map<uint16_t, IFD_Entry> parseTiffMeta(std::ifstream &file, bool verbose);
};

#endif
