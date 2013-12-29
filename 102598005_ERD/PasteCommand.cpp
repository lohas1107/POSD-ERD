#include "PasteCommand.h"

PasteCommand::PasteCommand(ERModel* model) : Command(model)
{
}

PasteCommand::~PasteCommand()
{
}

// 執行複製
void PasteCommand::execute()
{
	_model->paste();
}

// 反向執行複製
void PasteCommand::unexecute()
{
	_model->unPaste();
}
