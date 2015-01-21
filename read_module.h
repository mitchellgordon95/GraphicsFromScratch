#ifndef READ_MODULE_H
#define READ_MODULE_H 

#include "cli_module.h"
#include "dispatcher_module.h"
#include <vector>
#include <iostream>
#include <fstream>

// Implements the read command for the cli
class CLI_Read : public CLI_Module 
{
private:
    Dispatcher &dispatcher;
    
    // The number of times execute has been called recursively
    int depth_count;

    // Reads a CLI script and executes it 
    void execute(std::vector<char *> &params);
public:
    CLI_Read(Dispatcher &d): CLI_Module("read", 1), dispatcher(d), depth_count(0){};
    ~CLI_Read();
};

#endif
