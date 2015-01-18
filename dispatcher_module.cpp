#include "dispatcher_module.h"
#include "move_module.h"
#include "draw_module.h"
#include "color_module.h"
#include "read_module.h"
#include <cstddef>
#include <string.h>

// Since we override interpret, we don't care about the keyword etc.
Dispatcher::Dispatcher() : CLI_Module("", 0) 
{
    // Add all the modules we know about to a vector
    _modules.push_back(new CLI_Move());    
    _modules.push_back(new CLI_Draw());    
    _modules.push_back(new CLI_Color());    
    _modules.push_back(new CLI_Read(*this));
}

Dispatcher::~Dispatcher()
{
    for (size_t i = 0; i < _modules.size(); ++i)
        delete _modules[i];
}

bool Dispatcher::interpret(char * command) {
    // Parse the tokens into a vector
    std::vector<char *> tokens;
      
    char * next = strtok(command, ", ");
    while ( next != NULL)
    {
        tokens.push_back(next);
        next = strtok(NULL, ", ");
    } 
     
    // Convert the first token to lower case
    if(tokens.size() > 0)
        for (unsigned int i = 0; i < strlen(tokens[0]); ++i)
            tokens[0][i] = tolower(tokens[0][i]);

    return interpret(tokens);
}

bool Dispatcher::interpret(std::vector<char *> &command)
{
    // Pass the command to each module until one recognizes it.
    bool recognized = false;
    for (std::size_t i = 0; i < _modules.size(); ++i)
    {
        recognized =  _modules[i]->interpret(command);
        if (recognized)
            break;
    }
    
    return recognized;
}
