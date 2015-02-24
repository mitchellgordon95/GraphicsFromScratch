#ifndef CLI_MODULE_H
#define CLI_MODULE_H

#include <vector>
#include <cstddef>
#include <GL/glut.h>
#include "cli_global.h"

// The abstract interface class for all CLI modules
class CLI_Module 
{
private:
    // Derived classes should override this to perform
    // some meaningful tasks. 
    virtual void execute(std::vector<char *> &params) = 0; 

    // The keyword that a derived module is associated with
    const char * keyword;
    
    // The number of parameters this module expects
    size_t param_count;
public:
    // Constructor. Takes a keyword to associate the module with
    CLI_Module(const char * k, int p): keyword(k), param_count(p) {};

    // Virtual destructor
    virtual ~CLI_Module() {};

    // Interprets a command. Returns true if the command
    // was recognized, false if the command is not recognized. 
    // NOTE: expects all commands to be lower case
    bool interpret(std::vector<char *> &command);

    // A convenience function for parsing numerical arguments.
    static float parseNumericalArg(char * param);
};

#endif
