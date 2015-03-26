#ifndef DISPATCHER_MODULE_H
#define DISPATCHER_MODULE_H

#include "cli_module.h"

// The dispatcher multiplexes commands to individual modules
class Dispatcher : public CLI_Module 
{
private:
    std::vector< CLI_Module * > _modules;
    
    // The singleton instance of a dispatcher.
    static Dispatcher dispatcher;

    // Displays the help menu.
    void execute (std::vector<char *> &params);

    Dispatcher(); 
    ~Dispatcher();

public:
    // Returns the singleton instance of the dispatcher.
    static Dispatcher & getInstance();

    // Parses a string into tokens and converts the keyword to lower
    // case before passing command to modules
    bool interpret(char* command);
    // Passes command to all modules we know about
    bool interpret(std::vector<char *> &command);
};

#endif
