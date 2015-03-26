#!/bin/bash
echo -n "Keyword (read):"
read keyword 
echo -n "Number of Params (1):"
read param_count
echo -n "Help Documentation:"
read help_docs 

echo "#ifndef ${keyword^^}_MODULE_H
#define ${keyword^^}_MODULE_H

#include \"cli_module.h\"

// Implements the ${keyword} command for the cli
class CLI_${keyword^} : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
public:
    CLI_${keyword^}(): CLI_Module(\"${keyword}\", 0) {};
    ~CLI_${keyword^}();
    virtual const char * getHelp() { return \"$help_docs\"; }
};

#endif" > src/${keyword}_module.h

echo "#include \"${keyword}_module.h\"

CLI_${keyword^}::~CLI_${keyword^}()
{
}

void CLI_${keyword^}::execute(std::vector<char *> &params)
{
}" > src/${keyword}_module.cpp
