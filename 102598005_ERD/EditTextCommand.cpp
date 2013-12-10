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

// 執行編輯文字
void EditTextCommand::execute()
{
	_model->setNodeText(_index, _editText);
}

// 反向執行編輯文字
void EditTextCommand::unexecute()
{
	_model->setNodeText(_index, _previousText);
}
