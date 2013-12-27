#include "PasteCommand.h"

PasteCommand::PasteCommand(ERModel* model) : Command(model)
{
}

PasteCommand::~PasteCommand()
{
}

void PasteCommand::execute()
{
	_model->paste();
}

void PasteCommand::unexecute()
{
	_model->unPaste();
}
