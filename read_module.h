#ifndef READ_MODULE_H
#define READ_MODULE_H 

#include "cli_module.h"
#include "dispatcher_module.h"

// Implements the read command for the cli
class CLI_Read : public CLI_Module 
{
private:
    Dispatcher &dispatcher;
    
    // Number of times execute has been called recursively
    int call_depth;

    // Reads a CLI script and executes it 
    bool execute(std::vector<char *> &params);
public:
    CLI_Read(Dispatcher &d): CLI_Module("read", 3), dispatcher(d), call_depth(0) {};
    ~CLI_Read();
};

#endif
