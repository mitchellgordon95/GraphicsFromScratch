#include "dispatcher_module.h"
#include "move_module.h"
#include "draw_module.h"
#include "color_module.h"
#include <cstddef>

Dispatcher::Dispatcher() {
    _modules.push_back(new CLI_Move());    
    _modules.push_back(new CLI_Draw());    
    _modules.push_back(new CLI_Color());    
}

Dispatcher::~Dispatcher() {
    for (std::size_t i = 0; i < _modules.size(); ++i)
        delete _modules[i];
}

bool Dispatcher::execute(std::vector<char *> &command)
{
    // Pass the command to each module until one recognizes it.
    bool recognized = false;
    for (std::size_t i = 0; i < _modules.size(); ++i)
    {
        recognized =  _modules[i]->execute(command);
        if (recognized)
            break;
    }
    
    return recognized;
}
