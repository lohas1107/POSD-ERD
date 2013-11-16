#include "Command.h"

Command::Command()
{
}

Command::Command(ERModel* model)
{
	_model = model;
}

Command::~Command()
{
}
