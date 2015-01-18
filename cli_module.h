#ifndef CLI_MODULE_H
#define CLI_MODULE_H

#include <vector>

// The abstract interface class for all CLI modules
class CLI_Module 
{
private:
    // Derived classes should override this to perform
    // some meaningful tasks. Returns false by default
    virtual bool execute(std::vector<char *> &params) { return false; }

    // The keyword that a derived module is associated with
    const char * keyword;
    
    // The number of parameters this module expects
    int param_count;
public:
    // Constructor. Takes a keyword to associate the module with
    CLI_Module(const char * k, int p): keyword(k), param_count(p) {};

    // Virtual destructor
    virtual ~CLI_Module() {};

    // Interprets a command. Returns true on success,
    // false if the command is not recognized. 
    // NOTE: expects all commands to be lower case
    bool interpret(std::vector<char *> &command);
};
#endif
