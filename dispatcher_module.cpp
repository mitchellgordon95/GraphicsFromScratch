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

bool Dispatcher::interpret(char * command) 
{
    // Parse the tokens into a vector
    std::vector<char *> tokens;
      
    char * begin = command;
    char * end = command;
    
    // We parse tokens manually because we have wierd requirements with commas.
    while ( true )
    {
        // Go to the end of the token 
        while ( *end != ' ' && *end != '\t' && *end != ',' && *end != '\0' )
            ++end;

        // We hit the end of the string. Bail out.
        if ( *end == '\0' )
        {
            // There's one more token left to push
            if ( begin != end )
                tokens.push_back(begin);

            break;
        }

        // Use the delimeter space to mark the end of our token.
        *end = '\0';

        // Push the token
        tokens.push_back(begin);

        // Find the beginning of the next token.
        ++end;
        bool found_first_comma = false;

        while ( (*end == ' ' || *end == '\t' || *end == ',') && *end != '\0' )
        {
            // Multiple commas in the delimeter means empty tokens.
            if ( *end == ',' )
            {
                if (found_first_comma)
                    tokens.push_back("\0");
                
                found_first_comma = true;
            }
 
            ++end;
        }

        // We hit the end of the string. Bail out.
        if ( *end == '\0' )
            break;

        // We found the beginning of the next token.
        begin = end;
    } 
        
    /*char * next = strtok(command, " \t");
    while ( next != NULL)
    {
        tokens.push_back(next);
        next = strtok(NULL, " \t");
    } 
    */
     
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
