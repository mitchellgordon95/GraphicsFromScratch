#ifndef TIFF_UTILS_H
#define TIFF_UTILS_H
#include <stdint.h>
#include <string.h>
#include <map>
#include "endian_stream_reader.h"

// The possible value types for a TIFF IFD entry
enum Tiff_Value_Type { BYTE=1, ASCII=2, SHORT=3, LONG=4, RATIONAL=5, SBYTE=6,
                       UNDEFINED=7, SSHORT=8, SLONG=9, SRATIONAL=10, FLOAT=11,
                       DOUBLE=12 };

// Returns size of TIFF Type in bytes
int sizeOfType(Tiff_Value_Type type);

// A class for holding an IFD entry in TIFF files
class IFD_Entry {
public:
    uint16_t tag;
    Tiff_Value_Type type;
    uint32_t count;
    // A pointer to the value in dynamic memory.
    char * value;
    
    // Constructor
    IFD_Entry() {}

    // Copy Constructor
    IFD_Entry(const IFD_Entry &other);

    // Destructor
    ~IFD_Entry();

    // Read an IFD Entry from a file.
    static IFD_Entry readFromFile(std::ifstream &file, EndianStreamReader reader);
};

extern const std::map<int, const char *> Tiff_Tag_Names;

#endif
