#include "dispatcher_module.h"
#include <cstddef>
#include <string.h>
#include <iostream>
#include <vector>

// For the constructor definition, see dispatcher_module_init.cpp

// The singleton instance of this dispatcher
Dispatcher Dispatcher::dispatcher;

Dispatcher & Dispatcher::getInstance() {
	return dispatcher;
}

Dispatcher::~Dispatcher()
{
    for (size_t i = 0; i < _modules.size(); ++i)
        delete _modules[i];
}

void Dispatcher::execute(std::vector<char *> &params) {
		std::cout << "Known commands: " << std::endl;
		for (size_t i = 0 ; i < _modules.size() ; ++i)
			std::cout << "\t" << _modules[i]->getKeyword() << std::endl;
}

bool Dispatcher::interpret(char * command) 
{
    // Parse the tokens into a vector
    std::vector<char *> tokens;
      
    // The beginning of the current token
    char * begin = command;
    // The end of the current token.
    char * end = command;
    
    // A pointer to the null char at the end of the string.
    // We'll push this when there are empty tokens
    char * end_of_command = begin + strlen(begin);
    
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
                    tokens.push_back(end_of_command);
                
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
