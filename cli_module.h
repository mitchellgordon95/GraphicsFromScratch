#ifndef CLI_MODULE_H
#define CLI_MODULE_H

#include <vector>

// The abstract interface class for all CLI modules
class CLI_Module 
{
public:
    // Virtual destructor
    virtual ~CLI_Module() {};

    // Execute a command. Returns true on success,
    // false if the command is not recognized.
    // NOTE: expects all commands to be lower case
    virtual bool execute(std::vector<char *> &command) = 0;
};
#endif
