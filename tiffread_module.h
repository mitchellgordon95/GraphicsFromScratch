#ifndef TIFFREAD_MODULE_H
#define TIFFREAD_MODULE_H 

#include "cli_module.h"
#include "tiff_utils.h"

// Implements the TiffRead command for the cli
class CLI_TiffRead : public CLI_Module 
{
private:
	// The tags of the last tiff file read.
	static std::map<uint16_t, IFD_Entry> lastRead;

	// Reads in a Tiff file and displays it on the screen.
    void execute(std::vector<char *> &params);
public:
    CLI_TiffRead(): CLI_Module("tiffread", 1) {};
    ~CLI_TiffRead();

    // Returns the metadata of the last tiff file read
    static std::map<uint16_t, IFD_Entry> getLastRead() {return lastRead;}

};

#endif
