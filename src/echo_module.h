#ifndef ECHO_MODULE_H
#define ECHO_MODULE_H

#include "cli_module.h"
#include <iostream>

// Prints whatever it's passed to std::cout
class CLI_Echo: public CLI_Module
{
private:
    void execute(std::vector<char *> &params) {
    	std::cout << params[0] << std::endl;
    }
public:
    CLI_Echo(): CLI_Module("echo", 1) {};
    ~CLI_Echo() {};
};

#endif
