#include "PasteCommand.h"

PasteCommand::PasteCommand(ERModel* model) : Command(model)
{
}

PasteCommand::~PasteCommand()
{
}

// ����ƻs
void PasteCommand::execute()
{
	_model->paste();
}

// �ϦV����ƻs
void PasteCommand::unexecute()
{
	_model->unPaste();
}
