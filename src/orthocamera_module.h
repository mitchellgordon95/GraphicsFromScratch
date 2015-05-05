#ifndef ORTHOCAMERA_MODULE_H
#define ORTHOCAMERA_MODULE_H

#include "cli_module.h"

// Implements the orthocamera command for the cli
class CLI_Orthocamera : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Orthocamera(): CLI_Module("orthocamera", 0) {};
    ~CLI_Orthocamera();
    virtual const char * getHelp() { return "set an orthographic camera"; }
};

#endif
