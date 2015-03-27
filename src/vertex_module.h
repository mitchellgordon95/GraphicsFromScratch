#ifndef VERTEX_MODULE_H
#define VERTEX_MODULE_H

#include "cli_module.h"
#include <armadillo>

// Implements the vertex command for the cli
class CLI_Vertex : public CLI_Module
{
private:
    void execute(std::vector<char *> &params);
    arma::fvec first, second;
    bool have_first;

public:
    CLI_Vertex(): CLI_Module("vertex", 3), first(4), second(4), have_first(false) { };
    ~CLI_Vertex();
    virtual const char * getHelp() { return "vertex x,y,z: sets the first or second vertex of a line to be drawn. If the command is called twice, a line is drawn between the first vertex specified and the second vertex specified."; }
};

#endif
