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

// ����s�W����
void AddComponentCommand::execute()
{
	_model->addComponent(_type, _text);
}

// �ϦV����s�W����
void AddComponentCommand::unexecute()
{
	_model->deleteLastComponent();
}
