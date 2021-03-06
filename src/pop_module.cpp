#include "pop_module.h"
#include "cli_pipeline.h"

CLI_Pop::~CLI_Pop()
{
}

using namespace CLI_Pipeline;

void CLI_Pop::execute(std::vector<char *> &params)
{
	if (transform_stack.size() <= 1)
		throw std::runtime_error("The transform stack can't be empty.");

	transform_stack.pop_back();
	std::cout << "Popped a matrix off the transform stack." << std::endl;
}
