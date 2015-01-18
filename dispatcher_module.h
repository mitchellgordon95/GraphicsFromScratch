#ifndef DISPATCHER_MODULE_H
#define DISPATCHER_MODULE_H

#include "cli_module.h"

// The dispatcher multiplexes commands to individual modules
class Dispatcher : public CLI_Module 
{
private:
    std::vector<CLI_Module *> _modules;
public:
    Dispatcher();
    ~Dispatcher();
    bool execute(std::vector<char *> &command);
};

#endif
