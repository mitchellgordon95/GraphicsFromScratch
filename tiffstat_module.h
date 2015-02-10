#ifndef TIFFSTAT_MODULE_H
#define TIFFSTAT_MODULE_H 

#include "cli_module.h"
#include <stdint.h>
#include <fstream>
#include <map>

// A struct for holding an IFD entry in TIFF files
struct IFD_Entry {
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t value;
};

// The possible value types for a TIFF IFD entry
enum Tiff_Value_Type { BYTE=1, ASCII=2, SHORT=3, LONG=4, RATIONAL=5, SBYTE=6,
                       UNDEFINED=7, SSHORT=8, SLONG=9, SRATIONAL=10, FLOAT=11,
                       DOUBLE=12 };

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
    std::map<uint16_t, IFD_Entry> parseTiffMeta(std::ifstream &file, bool verbose);
};

#endif
