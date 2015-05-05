#ifndef TRACE_MODULE_H
#define TRACE_MODULE_H

#include "cli_module.h"

// Implements the trace command for the cli
class CLI_Trace : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_Trace(): CLI_Module("trace", 0) {};
    ~CLI_Trace();
    virtual const char * getHelp() { return "render the image"; }
};

#endif
