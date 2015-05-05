#ifndef PRINTCAMERA_MODULE_H
#define PRINTCAMERA_MODULE_H

#include "cli_module.h"

// Implements the printcamera command for the cli
class CLI_Printcamera : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Printcamera(): CLI_Module("printcamera", 0) {};
    ~CLI_Printcamera();
    virtual const char * getHelp() { return "prints the matrix associated with the camera transform"; }
};

#endif
