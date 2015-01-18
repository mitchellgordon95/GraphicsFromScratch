#include "dispatcher_module.h"
#include "move_module.h"
#include "draw_module.h"
#include "color_module.h"
#include "read_module.h"
#include <cstddef>

// Since we override interpret, we don't care about the keyword etc.
Dispatcher::Dispatcher() : CLI_Module("", 0) {
    // Add all the modules we know about to a vector
    _modules.push_back(new CLI_Move());    
    _modules.push_back(new CLI_Draw());    
    _modules.push_back(new CLI_Color());    
//    _modules.push_back(new CLI_Read(*this));
}

Dispatcher::~Dispatcher() {
    for (std::size_t i = 0; i < _modules.size(); ++i)
        delete _modules[i];
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
