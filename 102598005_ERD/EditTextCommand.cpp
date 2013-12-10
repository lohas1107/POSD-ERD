#include "EditTextCommand.h"

EditTextCommand::EditTextCommand(ERModel* model, int index, string previousText, string editText) : Command(model)
{
	_index = index;
	_previousText = previousText;
	_editText = editText;
}

EditTextCommand::~EditTextCommand()
{
}

// ����s���r
void EditTextCommand::execute()
{
	_model->setNodeText(_index, _editText);
}

// �ϦV����s���r
void EditTextCommand::unexecute()
{
	_model->setNodeText(_index, _previousText);
}
