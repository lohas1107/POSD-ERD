#include "AddComponentCommand.h"

AddComponentCommand::AddComponentCommand()
{
}

AddComponentCommand::AddComponentCommand(ERModel* model, pair<Type, string> type, string text) : Command(model)
{
	_type = type;
	_text = text;
}

AddComponentCommand::~AddComponentCommand()
{
}

// 執行新增元件
void AddComponentCommand::execute()
{
	_model->addComponent(_type, _text);
}

// 反向執行新增元件
void AddComponentCommand::unexecute()
{
	_model->deleteLastComponent();
}
